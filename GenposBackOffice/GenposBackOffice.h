// GenposBackOffice.h : main header file for the GenposBackOffice application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGenposBackOfficeApp:
// See GenposBackOffice.cpp for the implementation of this class
//

class CGenposBackOfficeApp : public CWinApp
{
public:
	CGenposBackOfficeApp();

public:

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGenposBackOfficeApp theApp;