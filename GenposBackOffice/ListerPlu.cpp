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

/*
 *  Retrieve the list of PLUs from the terminal.
 *
*/
short   CListerPlu::RetrieveList (void)
{
	CParamPlu::ParamPluKey tempPluKey;

	m_sLastError = 0;
	PluDataCount = 0;
	PluDataList.RemoveAll ();

	// read and keep reading PLUs untile there are no more.
	bool  bStart = true;
	short sCount = 0;
	while ( (sCount = PluData.RetrieveNextSet(bStart)) > 0) {
		bStart = false;
		for (int i = 0; i < sCount; i++) {
			tempPluKey = PluData.GetPluKey (i);
			if (tempPluKey.auchPluNo[0]) {
				// This is a valid PLU number so add it to our list.
				PluDataList.Add (tempPluKey);
				PluDataCount++;
			}
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