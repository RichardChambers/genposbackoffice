#include "StdAfx.h"
#include "ListerCoupon.h"

char const * const CListerCoupon::aszSqlDrop = "drop table CouponTable;";
char const * const CListerCoupon::aszSqlCreate = "create table CouponTable (akey int primary key not null, avalue blob);";
char const * const CListerCoupon::aszSqlInsert = "insert into CouponTable values (?1, ?2);";
char const * const CListerCoupon::aszSqlUpdate = "update CouponTable set avalue = ?2 where akey == ?1;";
char const * const CListerCoupon::aszSqlDelete = "delete from CouponTable where akey == ?1;";
char const * const CListerCoupon::aszSqlSelect = "select avalue from CouponTable where akey == ?1;";


CListerCoupon::CListerCoupon(void) :
	bCouponData(FALSE),
	CouponDataCount(0), CouponDataIndex(0),
	bCouponTotal(FALSE),
	CouponTotalCount(0), CouponTotalIndex(0),
	CouponData(0), CouponTotal(CTotal::TtlTypeNone)

{
}

CListerCoupon::~CListerCoupon(void)
{
}


short   CListerCoupon::RetrieveList (sqlite3 *db)
{
	m_sLastError = 1;
	CouponTotalIndex = CouponDataIndex = 0;
	CouponTotalCount = CouponDataCount = 1;

	return m_sLastError;
}

short   CListerCoupon::GetCurrentListItem (void)
{
	short  sRet = -1;

	if (CouponDataIndex < CouponDataCount) {
		sRet = CouponData.PullParam (CouponDataIndex);
	}

	bCouponData = (sRet == 0);
	if (bCouponData) CouponDataCount++; else CouponDataCount = CouponDataIndex;
	return -1;
}

short   CListerCoupon::GetNextListItem (void)
{
	if (CouponDataIndex <= CouponDataCount) {
		// we use <= in order to allow the index to go one past the max
		// we depend on GetCurrentListItem() to indicate past end of list.
		CouponDataIndex++;
	}

	return GetCurrentListItem (); 
}

short   CListerCoupon::GetFirstListItem (void)
{
	CouponDataIndex = 0;
	CouponDataCount = 1;

	return GetCurrentListItem ();
}

short   CListerCoupon::GetCurrentListTotal (void)
{
	short  sRet = -1;

	if (CouponTotalIndex < CouponTotalCount) {
		CouponTotal.setTotalCoupon (CouponTotalIndex);
		sRet = CouponTotal.RetrieveTotal ();
	}

	bCouponTotal = (sRet == 0);
	if (bCouponTotal) CouponTotalCount++; else CouponTotalCount = CouponTotalIndex;
	return -1;
}

short   CListerCoupon::GetNextListTotal (void)
{
	if (CouponTotalIndex <= CouponTotalCount) {
		// we use <= in order to allow the index to go one past the max
		// we depend on GetCurrentListItem() to indicate past end of list.
		CouponTotalIndex++;
	}

	return GetCurrentListTotal (); 
}

short   CListerCoupon::GetFirstListTotal (void)
{
	CouponTotalIndex = 0;
	CouponTotalCount = 1;

	return GetCurrentListTotal ();
}

short   CListerCoupon::GetCurrentListItemTotal (void)
{
	CouponTotalIndex = CouponDataIndex;

	return GetCurrentListTotal ();
}

short   CListerCoupon::GetCurrentListTotalItem (void)
{
	CouponDataIndex = CouponTotalIndex;

	return GetCurrentListItem ();
}
