// YellowButterflyDlg.h : ͷ�ļ�
//

#pragma once
struct User_AdapterInfo{
	char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
	CString	User_MAC;
	IP_ADDR_STRING* User_IP_AddressInfo;
	UCHAR Mac[6];
};

DWORD WINAPI RunTimeThread(LPVOID pParam);
DWORD WINAPI ListenBasThread(LPVOID pParam);
DWORD WINAPI CheckNetThread(LPVOID pParam);
DWORD WINAPI ListenInfoThread(LPVOID lpParameter);
DWORD WINAPI TimeCronThread(LPVOID lpParameter);
extern SOCKET ClientSocket;



// CYellowButterflyDlg �Ի���
class CYellowButterflyDlg : public CDialogEx
{
// ����
public:
	CYellowButterflyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YELLOWBUTTERFLY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	
	HICON m_hIcon;
	NOTIFYICONDATA nid;
	CStatusBar  m_wndStatusBar;              //״̬��
	HANDLE Work;
	HANDLE LoginThread;
	HANDLE ListenThread;
	HANDLE iListenThread;
	HANDLE hTimerCronThread;
	HWND UI_hwnd;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void StartLogin(CString Username,CString Passwd);
	afx_msg void DoLogOut();
	afx_msg void ReadIni();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void BanWindow(BOOL flag);
	afx_msg void AddNotifyInfo();
	afx_msg void OnIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void IsAlreadyRunning();
	afx_msg void AboutBox();
	afx_msg void DeleteNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HideWindows(WPARAM, LPARAM lParam);
	afx_msg LRESULT UpdateRunTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT LogOutMsg(WPARAM wParam,LPARAM lParam);
	afx_msg void CreatStatusBar();
	afx_msg void StartListenClient();
	afx_msg void SetLoginInfo(CString Username, CString Passwd);
	afx_msg CString AutoGetIP();
	afx_msg void ShowMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void CloseYellowButterfly();
	afx_msg void OnBnClickedCheckAutologin();
	afx_msg void OnBnClickedCheckRemember();
	afx_msg void SetWindowsCtrl();
	afx_msg void EXEAutoStart();
	afx_msg void LookThanks();
	afx_msg void LookUsage();
	afx_msg LRESULT TimeCron(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonTimercron();
	afx_msg void SetTimeCronThreaad();
	afx_msg void OnBnClickedCheckRelogin();
	afx_msg void OnBnClickedCheckLogintip();
};
