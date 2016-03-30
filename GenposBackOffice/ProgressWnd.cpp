// ProgressWnd.cpp : implementation file
//

#include "stdafx.h"
#include "GenposBackOffice.h"
#include "ProgressWnd.h"


// CProgressThread

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
	while (1) {
		Sleep(500);
		++i;
		if (m_ProgressBlock.m_CWnd) {
			CString  myText;
			myText.Format (L"T %d", i);
			m_ProgressBlock.m_CWnd->SetWindowText(myText);
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
		} else {
			m_ProgressThread->m_ProgressBlock.m_InProgress = 1 - m_ProgressThread->m_ProgressBlock.m_InProgress;
			m_ProgressThread->ResumeThread();
		}
	}

	return 0;
}
