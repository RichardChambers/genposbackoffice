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
	PluData.ClearParam ();      // initialize our receive buffer
	// read and keep reading PLUs untile there are no more.
	while ( (m_sLastError = ::SerOpPluAllRead(PluData.m_paraPlu, 0)) >= 0) {
		// The PLU read may return zero to 5 PLUs. We clear the PLU number area
		// so that we can detect if any PLUs were actually retrieved.
		// A read that is past the end of the PLUs stored will return a negative value.
		// However there is the possibility that before the read returns a negative
		// value it may return a zero error code but no PLUs.
		if (m_sLastError == 0) m_sLastError = 5;
		for (int i = 0; i < m_sLastError; i++) {
			tempPluKey = PluData.GetPluKey (i);
			if (tempPluKey.auchPluNo[0]) {
				// This is a valid PLU number so add it to our list.
				PluDataList.Add (tempPluKey);
				PluDataCount++;
			}
		}
		PluData.ClearPluKey();  // clear the data area to ready for the next set of PLUs.
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