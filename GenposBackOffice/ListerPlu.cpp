#include "StdAfx.h"
#include "ListerPlu.h"

CListerPlu::CListerPlu(void) :
	bPluData(FALSE),
	PluDataCount(0), PluDataIndex(0)
{
}

CListerPlu::~CListerPlu(void)
{
}


short   CListerPlu::RetrieveList (void)
{
	CParamPlu::ParamPluKey tempPluKey;

	m_sLastError = 0;
	PluDataCount = 0;
	PluDataList.RemoveAll ();
	PluData.ClearParam ();
	while ( (m_sLastError = ::SerOpPluAllRead(PluData.m_paraPlu, 0)) >= 0) {
		if (m_sLastError == 0) m_sLastError = 5;
		for (int i = 0; i < m_sLastError; i++) {
			tempPluKey = PluData.GetPluKey (i);
			PluDataList.Add (tempPluKey);
			PluDataCount++;
		}
	}

	return m_sLastError;
}

short   CListerPlu::GetCurrentListItem (void)
{
	short  sRet = -1;

	if (PluDataIndex < PluDataCount) {
		sRet = PluData.PullParam (PluDataList.GetAt(PluDataIndex));
	}

	bPluData = (sRet == 0);
	return -1;
}

short   CListerPlu::GetNextListItem (void)
{
	if (PluDataIndex <= PluDataCount) {
		// we use <= in order to allow the index to go one past the max
		// we depend on GetCurrentListItem() to indicate past end of list.
		PluDataIndex++;
	}

	return GetCurrentListItem (); 
}

short   CListerPlu::GetFirstListItem (void)
{
	PluDataIndex = 0;

	return GetCurrentListItem ();
}

short   CListerPlu::GetCurrentListTotal (void)
{
	short  sRet = -1;

	return -1;
}

short   CListerPlu::GetNextListTotal (void)
{
	return GetCurrentListTotal (); 
}

short   CListerPlu::GetFirstListTotal (void)
{

	return GetCurrentListTotal ();
}

short   CListerPlu::GetCurrentListItemTotal (void)
{

	return GetCurrentListTotal ();
}

short   CListerPlu::GetCurrentListTotalItem (void)
{

	return GetCurrentListItem ();
}

short  CListerPlu::BuildPluArray (void)
{
	RetrieveList ();
	int iCount = PluDataList.GetCount ();

	return 0;
}