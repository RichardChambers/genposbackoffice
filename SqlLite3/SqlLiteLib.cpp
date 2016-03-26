
#include "stdafx.h"

#include "SqlLiteLib.h"

CSqlLiteLib::CSqlLiteLib () : m_db(0), m_status(StatusDbNotOpen)
{
}

CSqlLiteLib::~CSqlLiteLib()
{
	Close ();
}

void CSqlLiteLib::Close (void)
{
	if (m_db) {
		sqlite3_close (m_db);
		m_db = 0;
	}
	m_status  = StatusDbNotOpen;
}

int CSqlLiteLib::Open (const char *dbName)
{
	m_status = StatusDbLastRqstGood;

	m_rc = sqlite3_open (dbName, &m_db);
    if (m_rc) {
      sqlite3_close (m_db);
	  m_db = 0;
	  m_status = StatusDbOpenError;
    }

	return m_status;
}

int CSqlLiteLib::ExecSql (const char *sqlText)
{
	m_status = StatusDbLastRqstGood;

	m_rc = sqlite3_exec (m_db, sqlText, 0, 0, 0);
    if (m_rc != SQLITE_OK) {
	  m_status = StatusDbLastRqstFail;
    }

	return m_status;
}

int CSqlLiteLib::ExecSql (const char *sqlText, CRecordProcessor *pProcessor)
{
	m_status = StatusDbLastRqstGood;

	if (pProcessor) {
		m_rc = sqlite3_exec (m_db, sqlText, pProcessor->pmyRecordProcessor, pProcessor, 0);
		if (m_rc != SQLITE_OK) {
			m_status = StatusDbLastRqstFail;
		}
	} else {
		m_status = StatusDbLastRqstFail;
	}

	return m_status;
}

int CSqlLiteLib::ExecSql (CSqlLiteLib::SqlLiteStmt sqlStmt)
{
	m_status = StatusDbLastRqstGood;

	return m_status;
}

int CSqlLiteLib::BindSql (const char *zValue, int iPos)
{
	m_status = StatusDbLastRqstGood;

    m_rc = sqlite3_bind_text(m_pStmt, iPos, zValue, -1, SQLITE_STATIC);

	return m_status;
}

int CSqlLiteLib::BindSql (const CSqlLiteLib::SqlLiteBlob zValue, int iPos)
{
	m_status = StatusDbLastRqstGood;

    m_rc = sqlite3_bind_blob(m_pStmt, iPos, zValue.m_pBlob, zValue.m_SizeBytes, SQLITE_STATIC);

	return m_status;
}

int CSqlLiteLib::PrepBeginSql (const char *sqlText)
{
	m_status = StatusDbLastRqstGood;

	m_rc = sqlite3_prepare(m_db, sqlText, -1, &m_pStmt, 0);
	if (m_rc != SQLITE_OK) {
		m_status = StatusDbLastRqstFail;
	}

	return m_status;
}

int CSqlLiteLib::PrepEndSql (void)
{
	m_status = StatusDbLastRqstGood;

	m_rc = sqlite3_finalize(m_pStmt);
	if (m_rc != SQLITE_OK) {
		m_status = StatusDbLastRqstFail;
	}

	return m_status;
}
