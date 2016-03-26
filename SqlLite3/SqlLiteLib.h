
#include "sqlite3.h"

// The struct used to contain the management date for returning the row results of
// a select.  In order to generailze this a bit, we also provide a function pointer
// to be used to provide the call back for the processing of the results set from
// a select.  This allows us to use the same select function with two different structs. 
typedef struct  {
	void  *pRecordSet;      // pointer to an array of one or more record structs, Tbl1Record
	int   nRecordSetMax;    // the maximum size of the array of record structs
	int   nRecordSetActual; // the actual number of results returned in elements of the array
	int  (*pmyRecordProcessor) (void *callBackArg, int argc, char **argv, char **azColName);
} CRecordProcessor;

class CSqlLiteLib
{
public:
	CSqlLiteLib ();
	virtual ~CSqlLiteLib();

	struct SqlLiteStmt {
		sqlite3_stmt *m_pStmt;
	};

	struct SqlLiteBlob {
		void  *m_pBlob;
		int   m_SizeBytes;
	};

	int Open (const char *dbName);
	void Close (void);

	int ExecSql (const char *sqlText);
	int ExecSql (const char *sqlText, CRecordProcessor *pProcessor);
	int ExecSql (CSqlLiteLib::SqlLiteStmt sqlStmt);

	int PrepBeginSql (const char *sqlText);
	int PrepEndSql (void);

	int BindSql (const char *zValue, int iPos);
	int BindSql (const CSqlLiteLib::SqlLiteBlob zValue, int iPos);

	const int GetLastRc (void);
	const int GetLastStatus (void);
	const SqlLiteStmt GetLastStmt (void);

	static const int StatusDbLastRqstGood  = 0;
	static const int StatusDbNotOpen       = -1;
	static const int StatusDbOpenError     = -2;
	static const int StatusDbLastRqstFail  = -3;
private:
	sqlite3 *m_db;   // data base handle from last SQLite open call
	int      m_rc;   // last return code from last SQLite function call
	int      m_status;
	sqlite3_stmt *m_pStmt;
	int      m_state;  // state machine step used with multiple step actions
};

inline 	const int CSqlLiteLib::GetLastRc (void) { return m_rc; }
inline 	const int CSqlLiteLib::GetLastStatus (void) { return m_status; }
inline  const CSqlLiteLib::SqlLiteStmt CSqlLiteLib::GetLastStmt (void) { SqlLiteStmt stmt; stmt.m_pStmt = m_pStmt; return stmt; }