/*
 * Copyright Richard Chambers, 2016
*/

// ProgressWnd.cpp : implementation file for CProgressWnd
//
// This class implements a progress control with its own animation
// in order to provide feedback to the user that some action is in
// progress which will take some time.
//
// This control is primarily used by the LAN functionality when performing a
// time consuming task such as transferring provisioning data from/to a terminal.
//
// The progress control animations is controlled by sending the control a user
// defined message along with any operands needed.

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "ProgressWnd.h"


// CProgressThread
// Thread that is used to modify the appearance of the progress control
// when animation is started. The thread periodically modifies the appearance
// of the control in order to inform the user an operation is in progress.

class CProgressThread : public CWinThread
{
	DECLARE_DYNCREATE(CProgressThread)

protected:
	CProgressThread();           // protected constructor used by dynamic creation
	virtual ~CProgressThread();

public:
	struct ProgressBlock {
		int  m_LastCommand;
		int  m_InProgress;
		CWnd *m_CWnd;
	};

	ProgressBlock m_ProgressBlock;

	CBitmap CBmpRunning1;
	CBitmap CBmpRunning2;
	CBitmap CBmpOff;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();

	afx_msg void OnProgressStart(WPARAM wParam,LPARAM lParam);
	afx_msg void OnProgressStop(WPARAM wParam,LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()
};


IMPLEMENT_DYNCREATE(CProgressThread, CWinThread)

CProgressThread::CProgressThread()
{
}

CProgressThread::~CProgressThread()
{
}

BOOL CProgressThread::InitInstance()
{
	CBmpRunning1.LoadBitmap (IDB_BITMAP_LANRUNNING1);  // Loads one of the default Windows bitmaps
	CBmpRunning2.LoadBitmap (IDB_BITMAP_LANRUNNING2);  // Loads one of the default Windows bitmaps
	CBmpOff.LoadBitmap (IDB_BITMAP_LAN_OFF);  // Loads one of the default Windows bitmaps
	return TRUE;
}

int CProgressThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
END_MESSAGE_MAP()


int CProgressThread::Run()
{

	int i = 0;
	int j = 0;
	while (1) {
		Sleep(500);
		++i;
		if (m_ProgressBlock.m_CWnd) {
			if (j)
				m_ProgressBlock.m_CWnd->SendMessage (STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBITMAP(CBmpRunning1)); 
			else
				m_ProgressBlock.m_CWnd->SendMessage (STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBITMAP(CBmpRunning2)); 
			j = 1 - j;
			CString  myText;
			myText.Format (L"T %d", i);
			m_ProgressBlock.m_CWnd->SetWindowText(myText);
		} else {
			i = 0;
		}
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------

// CProgressWnd

IMPLEMENT_DYNAMIC(CProgressWnd, CStatic)

CProgressWnd::CProgressWnd()
{
	m_ProgressThread = dynamic_cast<CProgressThread *>(AfxBeginThread(RUNTIME_CLASS(CProgressThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED));
	m_ProgressThread->m_ProgressBlock.m_CWnd = this;
	m_ProgressThread->m_ProgressBlock.m_LastCommand = 0;
	m_ProgressThread->m_ProgressBlock.m_InProgress = 0;
}

CProgressWnd::~CProgressWnd()
{
}

BEGIN_MESSAGE_MAP(CProgressWnd, CStatic)
	ON_MESSAGE(WM_LANPROGRESS, &CProgressWnd::OnProgressStartStop)
END_MESSAGE_MAP()

// CProgressWnd message handlers

LRESULT  CProgressWnd::OnProgressStartStop(WPARAM wParam, LPARAM lParam)
{
	if (m_ProgressThread) {
		m_ProgressThread->m_ProgressBlock.m_LastCommand = 0;
		if (m_ProgressThread->m_ProgressBlock.m_InProgress) {
			m_ProgressThread->SuspendThread();
			m_ProgressThread->m_ProgressBlock.m_InProgress = 1 - m_ProgressThread->m_ProgressBlock.m_InProgress;
			SendMessage (STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBITMAP(m_ProgressThread->CBmpOff)); 
		} else {
			SendMessage (STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)HBITMAP(m_ProgressThread->CBmpOff)); 
			m_ProgressThread->m_ProgressBlock.m_InProgress = 1 - m_ProgressThread->m_ProgressBlock.m_InProgress;
			m_ProgressThread->ResumeThread();
		}
	}

	return 0;
}
