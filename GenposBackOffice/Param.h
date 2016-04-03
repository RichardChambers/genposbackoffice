/*
 * CParam - the base class for the various types of parameter objects that are
 *          stored in the terminal.  Parameter objects contain provisioning data
 *          that is used during terminal operation.  Some types of parameters are
 *          used to constrain and modify the behavior of the software.  Other types
 *          of parameters contain operational data such as cashier data or PLU data
 *          which is used during operations.
 *
 *          The Param base class describes the basic methods and properties that all
 *          of the parameter objects will support.  Some parameter objects may not
 *          have all of the expected data or methods so they will provide a stub for
 *          those unsupported data and methods which will do nothing while providing
 *          a suitable return value.
**/

#pragma once

#include "R20_PC2172.h"

#include "a_globals.h"

class CParam
{
public:
	struct ParamClassStruct {
		UCHAR       uchMajorClass;      /* Major Class Data definition */
		UCHAR       uchMinorClass;      /* Minor Class Data definition */
	};

	CParam(void);
	virtual ~CParam(void);
	virtual short PullParam (void) = 0;
	virtual short PushParam (void) = 0;
	virtual void ClearParam (void) = 0;
	virtual char * GetSqliteKey (int i) = 0;
	virtual void * GetSqliteBlob (int i) = 0;
	virtual int  GetSqliteBlobSize (int i) = 0;

public:
	short     m_sLastError;
	short     m_bDataRead;
};
