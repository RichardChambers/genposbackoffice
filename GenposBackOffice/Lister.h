/*
 * CLister - the base class for the various types of lister objects.  Lister objects are
 *           objects used to sequentially list a type of object.  They are used to iterate
 *           over the range of an object type.
 *
 *           Many of the Lister derived objects have instances of both a parameter object
 *           derived from the CParam class and a total object derived from the CTotal class.
 *
 *           The CLister classes are designed to be sequential iterators to be used to iterate
 *           over a list of lister objects.  The derived class is responsible for determining
 *           how that is done.
**/

#pragma once

#include "R20_PC2172.h"

#include "a_globals.h"

class CLister
{
public:
	CLister(void);
	virtual ~CLister(void);

	virtual  short    RetrieveList (void) = 0;
	virtual  CLister  *getListObjectPtr (void) = 0;

	// functions for iterating over the list of parameter objects of a particular type.
	virtual  short    GetCurrentListItem (void) = 0;
	virtual  short    GetNextListItem (void) = 0;
	virtual  short    GetFirstListItem (void) = 0;

	// functions for iterating over the list of total objects of a particular type.
	virtual  short    GetCurrentListTotal(void) = 0;
	virtual  short    GetNextListTotal (void) = 0;
	virtual  short    GetFirstListTotal (void) = 0;

	// following two functions allow for retrieving either a CParam given a CTotal or
	// a CTotal given a CParam.  For example retrieve the provisioning data for a Cashier
	// and then using the Cashier also pull the total data for that particular Cashier.
	virtual  short    GetCurrentListItemTotal (void) = 0;
	virtual  short    GetCurrentListTotalItem (void) = 0;

public:
	short     m_sLastError;
};
