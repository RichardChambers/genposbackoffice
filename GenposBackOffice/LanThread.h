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
		int  m_LastCommand;         // last command or current command being processed
		int  m_InProgress;          // 1 if LAN action currently in progress
		void (*func)(void *obj, UINT msg, WPARAM wParam, LPARAM lParam);  // progress function
		void  *obj;                 // address of object that is target of progress function
	};

	LanBlock m_ThreadBlock;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnTerminalEJretrieve(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTerminalSettingsretrieve(WPARAM wParam,LPARAM lParam);

protected:
	bool ElectronicJournalRead (char *pFilePath, LanBlock *pLanBlock);
	bool ElectronicJournalReadReset (char *pFilePath, LanBlock *pLanBlock);
	bool RetrieveProvisioningData (char *pFilePath, LanBlock *pLanBlock);

	DECLARE_MESSAGE_MAP()
};


