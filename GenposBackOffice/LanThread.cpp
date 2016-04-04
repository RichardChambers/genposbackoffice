// LanThread.cpp : implementation file
//   The thread implemented by this class is to perform requests to a terminal
//   which can take a noticeable amount of time rather than having those actions
//   done in the main GUI loop.
//   The purpose of off loading these actions to this thread is to provide to the
//   user a responsive UI.

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "ListerPlu.h"
#include "ListerCoupon.h"
#include "ParamMajorDept.h"
#include "ListerCashier.h"
#include "ListerMnemonic.h"
#include "LanThread.h"

#include <memory.h>
#include "R20_PC2172.h"
#include <sqlite3.h>

/*
 *   The Electronic Journal of GenPOS is an electronic replica of a journal printer. The data that
 *   was printed to a journal printer is now printed to a file instead. This means that the data
 *   in the Electronic Journal is formatted, human readable text with a fixed print width that has
 *   no markup of any kind such as XML.
 *
 *   The Electronic Journal data is stored as a series of variable length records which contain a
 *   management header followed by one or more lines of formatted text with a fixed print width.
 *   The management header contains a count of the number of bytes in the Electronic Journal record
 *   along with other data such as a time stamp, the consecutive number for the record, and other
 *   data.
 *
 *   Some Electronic Journal entries may span more than one record. The consecutive number of several
 *   records for the same entry should be the same.
**/
class ElectronicJournalRecord {
public:
	ElectronicJournalRecord() : m_ulReadOffset(0), m_usBytesRead(0), m_usBufferOffset(0), m_sLastError(EJ_PERFORM) { memset (&m_ejtHeader, 0, sizeof(m_ejtHeader));}

	bool     ReadRecord (void);
	wchar_t  *GetLine (void);

	EJT_HEADER   m_ejtHeader;
	wchar_t      *m_pText;

private:
	ULONG        m_ulReadOffset;       // relative offset into EJ file specified in PCIF call when fetching the next set of records
	ULONG        m_usBytesRead;        // number of bytes read with the last EJ file read
	USHORT       m_usBufferOffset;     // offset within the current Electronic Journal entry
	USHORT       m_usRecordOffset;     // offset within the current record buffer
	SHORT        m_sLastError;
	UCHAR        m_auchEJBuffer[11000 + 32];  // max size of a record plus some extra room if full sized record retrieved.
};

bool ElectronicJournalRecord::ReadRecord(void)
{
	bool  bRetStatus = true;

	if (!((m_sLastError == EJ_PERFORM) || (m_sLastError == EJ_EOF))) {
		bRetStatus = false;
	} else {
		m_sLastError = ::SerEJReadFile(m_ulReadOffset, m_auchEJBuffer, sizeof(m_auchEJBuffer), &m_usBytesRead);
		TRACE3(" SerEJReadFile() m_ulReadOffset %d m_sLastError %d m_usBytesRead %d\n", m_ulReadOffset, m_sLastError, m_usBytesRead);
		if (m_usBytesRead && m_usBytesRead > sizeof(EJT_HEADER) && ((m_sLastError == EJ_PERFORM) || (m_sLastError == EJ_EOF))) {
			int  iOffset = 0;
			ULONG  ulReadOffset = m_ulReadOffset;

			m_ejtHeader = *(EJT_HEADER *)m_auchEJBuffer;  // get copy of the record header.
			TRACE3("    EJT_HEADER - signature 0x%4.4x, usCVLI %d consec %d \n", m_ejtHeader.usReserve, m_ejtHeader.usCVLI, m_ejtHeader.usConsecutive);
			m_usBufferOffset = sizeof(EJT_HEADER);       // point to beginning of the text string in record.
			m_ulReadOffset += m_ejtHeader.usCVLI;         // update our relative offset to beginning of next piece
			m_pText = (wchar_t*)(m_auchEJBuffer + m_usBufferOffset);
			iOffset = m_usBytesRead;
			ulReadOffset += m_usBytesRead;
			while (iOffset < m_ejtHeader.usCVLI && iOffset < sizeof(m_auchEJBuffer)) {
				m_sLastError = ::SerEJReadFile(ulReadOffset, m_auchEJBuffer + iOffset, sizeof(m_auchEJBuffer) - iOffset, &m_usBytesRead);
				TRACE3("      SerEJReadFile() ulReadOffset %d m_sLastError %d m_usBytesRead %d\n", ulReadOffset, m_sLastError, m_usBytesRead);
				ulReadOffset += m_usBytesRead;
				iOffset += m_usBytesRead;
			}
		} else {
			bRetStatus = false;
		}
	}
	return bRetStatus;
}

wchar_t  *ElectronicJournalRecord::GetLine (void)
{
	ReadRecord();
	memcpy (m_pText, m_auchEJBuffer + m_usBufferOffset, EJ_COLUMN * sizeof(wchar_t));
	m_pText[EJ_COLUMN] = 0;
	m_usBufferOffset += EJ_COLUMN * sizeof(wchar_t);
	return m_pText;
}


// CLanThread

IMPLEMENT_DYNCREATE(CLanThread, CWinThread)

CLanThread::CLanThread()
{
}

CLanThread::~CLanThread()
{
}

BOOL CLanThread::InitInstance()
{
	m_ThreadBlock.m_InProgress = 0;
	m_ThreadBlock.m_LastCommand = 0;
	return TRUE;
}

int CLanThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CLanThread, CWinThread)
	ON_THREAD_MESSAGE(ID_TERMINAL_EJRETRIEVE, &CLanThread::OnTerminalEJretrieve)
	ON_THREAD_MESSAGE(ID_TERMINAL_SETTINGSRETRIEVE, &CLanThread::OnTerminalSettingsretrieve)
END_MESSAGE_MAP()


// CLanThread message handlers

/*
 *    OnTerminalEJretrieve() - handle the ID_TERMINAL_EJRETRIEVE message
 *
 *    This function takes a path name and creates a copy of the Electronic Journal
 *    from the terminal into a text file.
 *
*/
void CLanThread::OnTerminalEJretrieve (WPARAM wParam, LPARAM lParam)
{
	// perform the Electronic Journal read putting it to a file.
	LanBlock *j = (LanBlock *)lParam;

	if (j) {
		j->m_InProgress = 1;
		j->m_LastCommand = ID_TERMINAL_EJRETRIEVE;
		j->func (j->obj, WM_LANPROGRESS, 0, 0);   // DispatchToAllViewsFunc()
	}

	m_ThreadBlock.m_InProgress = 1;

	m_ThreadBlock.m_LastCommand = ID_TERMINAL_EJRETRIEVE;

	// do the LAN activity and finish up.
	ElectronicJournalRead ((char *)wParam, 0);

	m_ThreadBlock.m_InProgress = 0;

	if (j) {
		j->m_InProgress = 0;
		j->func (j->obj, WM_LANPROGRESS, 0, 0);   // DispatchToAllViewsFunc()
	}
}

/*
 *    OnTerminalSettingsretrieve() - handle the ID_TERMINAL_SETTINGSRETRIEVE message
 *
 *    This function takes a path name and creates a copy of the provisioning of
 *    the terminal's provisioning information into a database file.
 *
*/
void CLanThread::OnTerminalSettingsretrieve (WPARAM wParam, LPARAM lParam)
{
	m_ThreadBlock.m_InProgress = 1;

	// perform the retrieval of the terminal settings read putting it to a file.
	LanBlock *j = (LanBlock *)lParam;

	if (j) {
		j->m_InProgress = 1;
		j->m_LastCommand = ID_TERMINAL_SETTINGSRETRIEVE;
		j->func (j->obj, WM_LANPROGRESS, 0, 0);   // DispatchToAllViewsFunc()
	}

	m_ThreadBlock.m_LastCommand = ID_TERMINAL_SETTINGSRETRIEVE;
	RetrieveProvisioningData ((char *)wParam, 0);

	if (j) {
		j->m_InProgress = 0;
		j->func (j->obj, WM_LANPROGRESS, 0, 0);   // DispatchToAllViewsFunc()
	}

	m_ThreadBlock.m_InProgress = 0;
}

bool CLanThread::ElectronicJournalRead (char *pFilePath, HWND hWndProgress)
{
	SHORT  sResult = ::SerEJNoOfTrans();  // check Electronic Journal status and get number of blocks.
	USHORT  usCount = 0;

	TRACE2("BEGIN CLanThread::ElectronicJournalRead - SerEJNoOfTrans() %d output file %s\n", sResult, pFilePath);

	ElectronicJournalRecord  EJ_RecData;

	if (pFilePath) {
		FILE *fp = fopen (pFilePath, "w+");
		while (EJ_RecData.ReadRecord()) {
			usCount++;
			int iEnd = (EJ_RecData.m_ejtHeader.usCVLI - sizeof(EJT_HEADER)) / 2;
			fprintf (fp, "----  consec No. %d   ---\n", EJ_RecData.m_ejtHeader.usConsecutive);
			for (int i = 0; i < iEnd; i += 24) {
				fprintf (fp, "%24.24S\n", EJ_RecData.m_pText + i);
			}
		}
		fclose (fp);
	}

	TRACE2("END - SerEJNoOfTrans() %d usCount %d\n", sResult, usCount);
	return true;
}

bool CLanThread::ElectronicJournalReadReset (char *pFilePath, HWND hWndProgress)
{
	return true;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	TRACE0("SQLite callback\n");
	for(int i = 0; i < argc; i++){
		TRACE2("   %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	TRACE0("\n");
	return 0;
}

static int  RetrieveProvisioningData_Plu (sqlite3 *db)
{
	int   rc;
	char  *zErrMsg = 0;
	// we use the PLU number as the key and the complete PLU data record from GenPOS
	// is stored as a BLOB.

	rc = sqlite3_exec(db, CListerPlu::aszSqlDrop, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec()  \"%s\" %d\n", CListerPlu::aszSqlDrop, rc);

	rc = sqlite3_exec(db, CListerPlu::aszSqlCreate, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec()  \"%s\" %d\n", CListerPlu::aszSqlCreate, rc);

	// read from GenPOS and keep reading PLUs untile there are no more.
	// for each PLU returned by GenPOS we will create a database record.
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, CListerPlu::aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare()  \"%s\" %d\n", CListerPlu::aszSqlInsert, rc);

	CParamPlu  PluData;
	bool  bStart = true;
	int   sCount = 0;
	while ( (sCount = PluData.RetrieveNextSet(bStart)) > 0) {
		bStart = false;
		for (int i = 0; i < sCount; i++) {
			char xKey[14] = {0};

			// convert the PLU number, stored as wchar_t, to char to create the table key.
			for (int j = 0; j < 14; j++) xKey[j] = (char)PluData.m_paraPlu[i].auchPluNo[j];

			// bind the key to the first parameter of the insert, the key value
			rc = sqlite3_bind_text (insertStmt, 1, xKey, 14, SQLITE_STATIC);
			TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

			// bind the PLU data to the second parameter of the insert, the data value
			rc = sqlite3_bind_blob (insertStmt, 2, PluData.m_paraPlu + i, sizeof(PluData.m_paraPlu[0]), SQLITE_STATIC);
			TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

			// perform the actual insert with the modified prepared statement
			rc = sqlite3_step (insertStmt);
			TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

			// reset the prepared statement so that we do our next set of binds.
			rc = sqlite3_reset (insertStmt);
			TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);
		}
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}


static int  RetrieveProvisioningData_Cashier (sqlite3 *db)
{
	int   rc;
	char  *zErrMsg = 0;

	rc = sqlite3_exec(db, CListerCashier::aszSqlDrop, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", CListerCashier::aszSqlDrop, rc);

	rc = sqlite3_exec(db, CListerCashier::aszSqlCreate, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", CListerCashier::aszSqlCreate, rc);

	// read from GenPOS and keep reading PLUs untile there are no more.
	// for each PLU returned by GenPOS we will create a database record.
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, CListerCashier::aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", CListerCashier::aszSqlInsert, rc);

	CListerCashier  cashierList;
	cashierList.RetrieveList();

	short sStatus = cashierList.GetFirstListItem();
	while ( sStatus >= 0) {
		CParamCashier::CASIF_ETK  dataBlob = {0};
		char       xKey[14] = {0};

		// convert the PLU number, stored as wchar_t, to char to create the table key.
		sprintf (xKey, "%10.10d", cashierList.CashierData.m_paraCashier.ulCashierNo);
		dataBlob.m_paraCashier = cashierList.CashierData.m_paraCashier;
		dataBlob.m_jobETK = cashierList.CashierData.m_jobETK;

		// bind the key to the first parameter of the insert, the key value
		rc = sqlite3_bind_text (insertStmt, 1, xKey, 10, SQLITE_STATIC);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// bind the PLU data to the second parameter of the insert, the data value
		rc = sqlite3_bind_blob (insertStmt, 2, &dataBlob, sizeof(dataBlob), SQLITE_STATIC);
		TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

		// perform the actual insert with the modified prepared statement
		rc = sqlite3_step (insertStmt);
		TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (insertStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);

		sStatus = cashierList.GetNextListItem();
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}


static int  RetrieveProvisioningData_Department (sqlite3 *db)
{
	int   rc;
	char  *zErrMsg = 0;
	char  *aszSqlDrop = "drop table DeptTable;";
	// we use the PLU number as the key and the complete PLU data record from GenPOS
	// is stored as a BLOB.
	char  *aszSqlCreate = "create table DeptTable (akey int primary key not null, avalue blob);";
	char  *aszSqlInsert = "insert into DeptTable values (?, ?);";

	rc = sqlite3_exec(db, aszSqlDrop, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", aszSqlDrop, rc);

	rc = sqlite3_exec(db, aszSqlCreate, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", aszSqlCreate, rc);

	// read from GenPOS and keep reading PLUs untile there are no more.
	// for each PLU returned by GenPOS we will create a database record.
	sqlite3_stmt  *insertStmt;
	rc = sqlite3_prepare(db, aszSqlInsert, -1, &insertStmt, NULL);
	TRACE2("   sqlite3_prepare() \"%s\" %d\n", aszSqlInsert, rc);

//	CListerCashier  cashierList;
//	cashierList.RetrieveList();

	CParamMinorDept  minorDept;

//	short sStatus = cashierList.GetFirstListItem();
	short sStatus = 0;
	while ( sStatus >= 0) {
		// bind the key to the first parameter of the insert, the key value
		rc = sqlite3_bind_int (insertStmt, 1, minorDept.m_paraDept.usDeptNo);
		TRACE1("   sqlite3_bind_text() bind text key %d\n", rc);

		// bind the PLU data to the second parameter of the insert, the data value
		rc = sqlite3_bind_blob (insertStmt, 2, &minorDept.m_paraDept, sizeof(minorDept.m_paraDept), SQLITE_STATIC);
		TRACE1("   sqlite3_bind_blob() bind blob value %d\n", rc);

		// perform the actual insert with the modified prepared statement
		rc = sqlite3_step (insertStmt);
		TRACE2("   sqlite3_step() step insert (%d is SQLITE_DONE) %d\n", SQLITE_DONE, rc);

		// reset the prepared statement so that we do our next set of binds.
		rc = sqlite3_reset (insertStmt);
		TRACE1("   sqlite3_reset() prepared stmt reset %d\n", rc);

//		sStatus = cashierList.GetNextListItem();
	}

	// we are done with the prepared statement so release all the resources for it.
	rc = sqlite3_finalize (insertStmt);
	TRACE1("   sqlite3_finalize() prepared stmt reset %d\n", rc);

	return 1;
}

static int  RetrieveProvisioningData_TransMnemo (sqlite3 *db)
{
	int     rc;
	char    *zErrMsg = 0;

	rc = sqlite3_exec(db, CListerTransaction::aszSqlDrop, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", CListerTransaction::aszSqlDrop, rc);

	rc = sqlite3_exec(db, CListerTransaction::aszSqlCreate, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", CListerTransaction::aszSqlCreate, rc);

	CListerTransaction::RetrieveAndStoreOnly (db);

	return 1;
}

static int  RetrieveProvisioningData_LeadthruMnemo (sqlite3 *db)
{
	int     rc;
	char    *zErrMsg = 0;

	rc = sqlite3_exec(db, CListerLeadThru::aszSqlDrop, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", CListerLeadThru::aszSqlDrop, rc);

	rc = sqlite3_exec(db, CListerLeadThru::aszSqlCreate, NULL, 0, &zErrMsg);
	TRACE2("   sqlite3_exec() \"%s\" %d\n", CListerLeadThru::aszSqlCreate, rc);

	CListerLeadThru::RetrieveAndStoreOnly (db);

	return 1;
}

/*
 *    RetrieveProvisioningData() - handle the ID_TERMINAL_SETTINGSRETRIEVE message
 *
 *    This function takes a path name and creates a copy of the provisioning of
 *    the terminal's provisioning information into a database file.
 *
*/
bool CLanThread::RetrieveProvisioningData (char *pFilePath, HWND hWndProgress)
{
	sqlite3 *db;

	// truncate the file.
	FILE *fp = fopen (pFilePath, "w");
	fclose (fp);

	int rc = sqlite3_open(pFilePath, &db);
	if( rc != SQLITE_OK ) {
		TRACE1("  ERROR sqlite3_open() %d\n", rc);
		return true;
	}

	RetrieveProvisioningData_Plu (db);
	RetrieveProvisioningData_Cashier (db);
	RetrieveProvisioningData_TransMnemo (db);
	RetrieveProvisioningData_LeadthruMnemo (db);

	// close the SQLite file as we are done making database changes.
	sqlite3_close(db);
	return true;
}