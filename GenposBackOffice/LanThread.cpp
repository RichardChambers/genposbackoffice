// LanThread.cpp : implementation file
//   The thread implemented by this class is to perform requests to a terminal
//   which can take a noticeable amount of time rather than having those actions
//   done in the main GUI loop.
//   The purpose of off loading these actions to this thread is to provide to the
//   user a responsive UI.

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "LanThread.h"

#include <memory.h>
#include "R20_PC2172.h"

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
END_MESSAGE_MAP()


// CLanThread message handlers

void CLanThread::OnTerminalEJretrieve(WPARAM wParam,LPARAM lParam)
{
	// perform the Electronic Journal read putting it to a file.

	m_ThreadBlock.m_InProgress = 1;
	m_ThreadBlock.m_LastCommand = ID_TERMINAL_EJRETRIEVE;

	// do the LAN activity and finish up.
	ElectronicJournalRead ((char *)wParam, 0);

	m_ThreadBlock.m_InProgress = 0;
	*(LONG *)lParam = 0;
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
