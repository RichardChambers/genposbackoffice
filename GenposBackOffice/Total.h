/*
 * CTotal - the base class for the various types of total objects that are
 *          stored in the terminal.  Total objects contain total data or measurements
 *          that provide information about how often an object is used within the terminal.
 *
 *          Generally a total object contains various kind of financial amounts and usage
 *          counts.  A total object shadows an actual data object or parameter object
 *          such as a cashier or a register or a PLU and each time the parameter object is
 *          involved in an operation, e.g. ringing up a PLU, the appropriate total objects
 *          are updated.  A particular action may affect more than one total object as we
 *          may be interested in rolling up measurements of various kinds.
 *
 *          So ringing up a PLU may affect the PLU totals for the PLU followed by
 *          changes to the cashier totals for the cashier who rang up the item and the
 *          terminal (register) financial totals for the terminal used to ring up the item.
**/

#pragma once

#include "R20_PC2172.h"

#include "a_globals.h"

class CTotal
{
public:
	enum TtlType {TtlTypeNone = 0, TtlTypeCurDay = 1, TtlTypeSaveDay = 2, TtlTypeCurPtd = 3, TtlTypeSavePtd = 4};

	typedef unsigned char TtlClass;

	struct TtlClassStruct {
		UCHAR       uchMajorClass;      /* Major Class Data definition */
		UCHAR       uchMinorClass;      /* Minor Class Data definition */
	};


	CTotal(CTotal::TtlClass major = 0, CTotal::TtlType type = CTotal::TtlTypeNone);
	virtual ~CTotal(void);
	virtual TtlClassStruct *getTotalStructPtr (void) = 0;

	//	CLASS_TTLCURDAY     1       /* Current Daily File */
	//	CLASS_TTLSAVDAY     2       /* Previous Daily File */
	//	CLASS_TTLCURPTD     3       /* Current Period To Day File */
	//	CLASS_TTLSAVPTD     4       /* Previous Period To Day File */
	//	CLASS_SAVED_TOTAL	5

	short RetrieveTotal (void);
	short ResetTotal (void);
	short ResetTotalEndOfDay (void);

protected:
	unsigned char DetermineMinorClass (TtlType type);

public:
	TtlClass  m_ttlClass;
	TtlType   m_ttlType;
	BOOL      m_bTotalRetrieved;
	BOOL      m_bTotalReset;
	short     m_sLastError;
	unsigned short  m_mdcResetInd;
	unsigned short  m_mdcResetEndOfDay;

// -------------------------------------------------------------
// Parameters for a Reset and for an End Of Day Reset.

// following is used to indicate a reset of a particular type of data and is
// used with the major class identifier for the type of data.
static const USHORT NOT_EOD            = 0x0000;

static const USHORT CASHIER_RESET      = 0x0000;
static const USHORT INDFIN_RESET       = 0x0100;


// following are used for End of Day with a major code of CLASS_TTLEODRESET
// rather than the major class identifier for the type of data.
static const USHORT EOD_REGFIN         = static_cast< const USHORT >( ~0x0001 );
static const USHORT EOD_DEPT           = static_cast< const USHORT >( ~0x0002 );
static const USHORT EOD_PLU            = static_cast< const USHORT >( ~0x0004 );
static const USHORT EOD_HOURLY         = static_cast< const USHORT >( ~0x0008 );
static const USHORT EOD_COUPON         = static_cast< const USHORT >( ~0x0080 );
static const USHORT EOD_INDFIN         = static_cast< const USHORT >( ~0x0100 );
static const USHORT EOD_SERVTIME       = static_cast< const USHORT >( ~0x0200 );

};
