#pragma once



// CLanThread
//   Used to perform time consuming LAN communications and data transfers.
//   This class allows for UI responsiveness during actions such as
//   polling the Electronic Journal, doing End of Day, etc.

class CLanThread : public CWinThread
{
	DECLARE_DYNCREATE(CLanThread)

protected:
	CLanThread();           // protected constructor used by dynamic creation
	virtual ~CLanThread();

public:
	struct LanBlock {
		int  m_LastCommand;
		int  m_InProgress;
	};

	LanBlock m_ThreadBlock;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnTerminalEJretrieve(WPARAM wParam,LPARAM lParam);

protected:
	bool ElectronicJournalRead (char *pFilePath, HWND hWndProgress);
	bool ElectronicJournalReadReset (char *pFilePath, HWND hWndProgress);

	DECLARE_MESSAGE_MAP()
};


