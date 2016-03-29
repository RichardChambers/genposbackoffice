#pragma once


// CProgressWnd
class CProgressThread;        // forward declaration for a view only class for progress animation.

class CProgressWnd : public CStatic
{
	DECLARE_DYNAMIC(CProgressWnd)

public:
	CProgressWnd();
	virtual ~CProgressWnd();

	LRESULT  CProgressWnd::OnProgressStartStop(WPARAM wParam, LPARAM lParam);

protected:
	CProgressThread    *m_ProgressThread;

	DECLARE_MESSAGE_MAP()
};


