
// YellowButterflyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YellowButterfly.h"
#include "YellowButterflyDlg.h"
#include "afxdialogex.h" 
#include "EXIT.h" 
#include "md5.h"
#include "UserSetting.h" 
#include "AboutBox.h" 
#include "Thanks.h"
#include "UdpClient.h"
#include "ShowTip.h"
#include "Usage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BOOL AutoLoadIp = TRUE;
BOOL AutoLogin = FALSE;
BOOL RememberPasswd = FALSE;
BOOL IsLogin = FALSE;
BOOL ListenRunFlags = TRUE;
BOOL TimeCronFlags = FALSE;

SOCKET BasSocket;
CString RecvData;
SOCKET ClientSocket;
UdpClient *Client;
long Minute = 0;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���




// CYellowButterflyDlg �Ի���




CYellowButterflyDlg::CYellowButterflyDlg(CWnd* pParent )
	: CDialogEx(CYellowButterflyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYellowButterflyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CYellowButterflyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CYellowButterflyDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CYellowButterflyDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_ABOUTBOX, &CYellowButterflyDlg::AboutBox)
	ON_BN_CLICKED(ID_AUTO_START, &CYellowButterflyDlg::EXEAutoStart)
	ON_BN_CLICKED(ID_STOP_START, &CYellowButterflyDlg::EXEAutoStart)
	ON_BN_CLICKED(IDC_THANK, &CYellowButterflyDlg::LookThanks)
	ON_BN_CLICKED(ID_USAGE, &CYellowButterflyDlg::LookUsage)
	ON_MESSAGE(WM_DELETE_NOTIFY, (LRESULT(__thiscall CWnd::*)(WPARAM, LPARAM))DeleteNotify)
	ON_MESSAGE(WM_NOTIFYMSG, (LRESULT(__thiscall CWnd::*)(WPARAM, LPARAM))ShowMsg)
	ON_MESSAGE(WM_HIDE_WINDOWS, HideWindows)
	ON_MESSAGE(WM_UPDATE_RUN_TIME, UpdateRunTime)
	ON_MESSAGE(WM_LOGOUT,LogOutMsg)
	ON_MESSAGE(WM_TIMECRONOVER, TimeCron)
	ON_MESSAGE(UM_ICONNOTIFY, (LRESULT(__thiscall CWnd::*)(WPARAM, LPARAM))OnIconNotify)
	ON_BN_CLICKED(IDC_CHECK_AUTOLOGIN, &CYellowButterflyDlg::OnBnClickedCheckAutologin)
	ON_BN_CLICKED(IDC_CHECK_REMEMBER, &CYellowButterflyDlg::OnBnClickedCheckRemember)
	ON_BN_CLICKED(IDC_BUTTON_TimerCron, &CYellowButterflyDlg::OnBnClickedButtonTimercron)
	ON_BN_CLICKED(IDC_CHECK_RELOGIN, &CYellowButterflyDlg::OnBnClickedCheckRelogin)
	ON_BN_CLICKED(IDC_CHECK_LOGINTIP, &CYellowButterflyDlg::OnBnClickedCheckLogintip)
END_MESSAGE_MAP()


// CYellowButterflyDlg ��Ϣ�������

BOOL CYellowButterflyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SkinH_Attach();
	::SkinH_AttachEx("skinh.she", NULL);
	IsAlreadyRunning();
	Sleep(10);
	//LoginService = &(::GetAdapter());
	::GetAdapter();
	UI_hwnd = this->GetSafeHwnd();
	this->ReadIni();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	this->AddNotifyInfo();
	this->CreatStatusBar();
	this->StartListenClient();
	CRect rect;
	GetWindowRect(&rect);
	rect.bottom += 50;
	MoveWindow(rect);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYellowButterflyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}



//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CYellowButterflyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CYellowButterflyDlg::OnSize(UINT nType, int cx, int cy)
{
	if (m_wndStatusBar.m_hWnd != NULL){    //���Ի����С�ı�ʱ ״̬����СҲ��֮�ı�
		CRect rc;
		rc.top = cy - 25;
		rc.left = 0;
		rc.right = cx;
		rc.bottom = cy;
		m_wndStatusBar.MoveWindow(rc);
		m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_POPOUT, cx - 1);
		//	m_wndStatusBar.SetPaneText(0, "�ȴ�����....");
	}

	switch (nType)
	{

	case SIZE_MINIMIZED:
		ShowWindow(SW_HIDE);
		break;
	}
}

void CYellowButterflyDlg::AboutBox()
{


	CAboutDlg About;
	About.DoModal();
}

static UINT indicators[] =
{
	IDR_STATUSBAR_STRING
};

void CYellowButterflyDlg::CreatStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators) / sizeof(UINT)))                    //����״̬���������ַ���Դ��ID
	{
		TRACE0("Failed to create status bar\n");
		return;      // fail to create
	}
	CRect rc;
	::GetWindowRect(m_wndStatusBar.m_hWnd, rc);
	m_wndStatusBar.MoveWindow(rc);                              //�ƶ�״̬����ָ��λ��

}

void CYellowButterflyDlg::OnBnClickedButtonLogin()
{
   if (!IsLogin)
   {
	 CString Username, Password;
	 GetDlgItem(IDC_EDIT_USERNAME)->GetWindowTextA(Username);
	 GetDlgItem(IDC_EDIT_PASSWD)->GetWindowTextA(Password);
	if (!LoginService.AdapterName.IsEmpty())
	 {
	 this->StartLogin(Username, Password);
	 Sleep(2);
	 IsLogin = TRUE;
	}
	else{
		AfxMessageBox("û�в����߻�����WIFI��!\r\r\n����ô����?");
	 }
	}
	else
	{
		this->DoLogOut();
		Client->SendLogoutPack();
	}

}


LRESULT CYellowButterflyDlg::UpdateRunTime(WPARAM wParam, LPARAM lParam)
{
	m_wndStatusBar.SetPaneText(0, (LPSTR)wParam);
	return 1;
}

void CYellowButterflyDlg::IsAlreadyRunning()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, AfxGetAppName());
	if (GetLastError() == ERROR_ALREADY_EXISTS)

	{
		AfxMessageBox("�ó���ֻ������һ��");
		exit(0);

	}
	if (hMutex)

	{
		::ReleaseMutex(hMutex);

	}
}

void CYellowButterflyDlg::StartLogin(CString Username, CString Passwd)
{
	   ::SaveLogin(Username, Passwd, RememberPasswd);
	//if (IsChangeMac == false){
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("����");
		this->SetWindowsCtrl();
		SetLoginInfo(Username, Passwd);
		Client->SetServer(LoginService.ServerAddr);
		Client->SendLoginPack(LoginService.Mac, LoginService.UserName.GetBuffer(), LoginService.Password.GetBuffer(), LoginService.LocalIp.GetBuffer(), LoginService.Service.GetBuffer(), 1, "3.8.3");
		LoginThread = CreateThread(NULL, NULL, CheckNetThread, UI_hwnd, NULL, NULL);
		iListenThread = CreateThread(NULL, NULL, ListenInfoThread, UI_hwnd, NULL, NULL);
		m_wndStatusBar.SetPaneText(0, "���ڵ�¼....");
	//}
	//else{
	//	MessageBox("�벻Ҫ˽�¸���MAC��ַ!","Warning",NULL);
	//}
}

void CYellowButterflyDlg::SetWindowsCtrl()
{
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(IsLogin);
	GetDlgItem(IDC_EDIT_PASSWD)->EnableWindow(IsLogin);
	GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(IsLogin);
	//GetDlgItem(IDC_CHECK_AUTOLOGIN)->EnableWindow(IsLogin);
	GetDlgItem(IDC_CHECK_REMEMBER)->EnableWindow(IsLogin);
	//GetDlgItem(IDC_CHECK_RELOGIN)->EnableWindow(IsLogin);
	GetDlgItem(IDC_CHECK_LOGINTIP)->EnableWindow(IsLogin);
}

void CYellowButterflyDlg::SetLoginInfo(CString Username, CString Passwd)
{
	CString fPath = GetFilePath() + "Config.ini";
	CString IfAutoLoadIp;
	LoginService.Service = ::LoadIni("�������", fPath);
	LoginService.ServerAddr = LoadIni("��֤������", fPath);
	LoginService.UserName = Username;
	LoginService.Password = Passwd;
	IfAutoLoadIp=::LoadIni("����ip", fPath);
	if (AutoLoadIp || (IfAutoLoadIp.CompareNoCase("auto")==0))
	{
		LoginService.LocalIp = this->AutoGetIP();
	}
	else{
		LoginService.LocalIp = LoadIni("����ip", fPath);
	}

}

LRESULT CYellowButterflyDlg::LogOutMsg(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void CYellowButterflyDlg::DoLogOut()
{
	GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("����");
	this->SetWindowsCtrl();
	TerminateThread(Work, NULL);
	Sleep(100);
	CloseHandle(Work);
	m_wndStatusBar.SetPaneText(0, "�ȴ�����....");
	Sleep(2);
	IsLogin = FALSE;
}



void CYellowButterflyDlg::StartListenClient()
{
	Sleep(50);
	ListenThread = CreateThread(NULL, NULL, ListenBasThread, UI_hwnd, NULL, NULL);
	if (AutoLogin)
	{
		Sleep(200);
		CString AutoUsername, AutoPassword;
		GetDlgItem(IDC_EDIT_USERNAME)->GetWindowTextA(AutoUsername);
		GetDlgItem(IDC_EDIT_PASSWD)->GetWindowTextA(AutoPassword);
		if (AutoUsername.GetLength() >= 1 && AutoPassword.GetLength() >= 1)
		{
			this->OnBnClickedButtonLogin();
		}
	}
	
}

void CYellowButterflyDlg::OnBnClickedButtonSetting()
{


	CUserSetting dlgSetting;
	dlgSetting.DoModal();

}

void CYellowButterflyDlg::ReadIni()
{
	CString FilePath = ::GetFilePath();
	FilePath += "Config.ini";
	CString  Contents, Result;
	char sResult[MAX_PATH];
	DWORD dwResult, iSize = 256;
	dwResult = GetPrivateProfileSection("�û�������Ϣ", sResult, iSize, FilePath);
	if (dwResult > 0)
	{
		char item[256];
		int  len = 0;
		int strEnd = 0x00;
		memset(item, 0x00, sizeof(item));
		for (int i = 0; i<dwResult; i++)
		{
			if (sResult[i] != strEnd)
			{
				item[len] = sResult[i];
				len++;
			}
			else
			{
				char* pdest;
				char key[256], data[256];
				pdest = strchr(item, '=');
				memset(key, 0x00, sizeof(key));
				memcpy(key, item, pdest - item);
				memset(data, 0x00, sizeof(data));
				strcpy(data, pdest + 1);

				Contents.Format("%s", data);
				if (strcmp(key, "�����ʺ�") == 0){
					GetDlgItem(IDC_EDIT_USERNAME)->SetWindowTextA(Contents);
					//LoginService.UserName = Contents;
					
				}
				else if (strcmp(key, "��������") == 0){
					GetDlgItem(IDC_EDIT_PASSWD)->SetWindowTextA(Contents);
					//LoginService.Password = Contents;
				}
				else if (strcmp(key, "����ip") == 0)
				{
					if (Contents.CompareNoCase("auto") != 0){ AutoLoadIp = FALSE; }
				}
				else if (strcmp(key, "��ס����") == 0){
					if (Contents.CompareNoCase("Yes") == 0)
					{
						CButton*	pBtn = (CButton*)GetDlgItem(IDC_CHECK_REMEMBER);
						pBtn->SetCheck(1);
						RememberPasswd = TRUE;
					}
				}
				else if (strcmp(key, "�Զ���¼") == 0){
					if (Contents.CompareNoCase("Yes") == 0){
						CButton*	pBtn = (CButton*)GetDlgItem(IDC_CHECK_AUTOLOGIN);
						pBtn->SetCheck(1);
						AutoLogin = TRUE;
					}
				}
				else if (strcmp(key, "��������") == 0){
					if (Contents.CompareNoCase("Yes") == 0){
						CButton*	pBtn = (CButton*)GetDlgItem(IDC_CHECK_RELOGIN);
						pBtn->SetCheck(1);
						ReLoginFlags = TRUE;
					}
				}
				else if (strcmp(key, "��¼��ʾ") == 0){
					if (Contents.CompareNoCase("Yes") == 0){
						CButton*	pBtn = (CButton*)GetDlgItem(IDC_CHECK_LOGINTIP);
						pBtn->SetCheck(1);
						LoginTipFlags = TRUE;
					}
				}
				memset(item, 0x00, sizeof(item));
				len = 0;
				if (sResult[i + 1] == strEnd)
				{
					break;
				}
			}
		}
	}
	else{
		CButton*	pBtn = (CButton*)GetDlgItem(IDC_CHECK_LOGINTIP);
		pBtn->SetCheck(1);
		LoginTipFlags = TRUE;
		::CreateDefaultIni(FilePath);
	}
}

void CYellowButterflyDlg::AddNotifyInfo()
{
	nid.cbSize = sizeof(nid);     //��С��ֵ
	nid.hWnd = m_hWnd;           //������
	nid.uID = IDR_MAINFRAME;     //icon  ID
	nid.uTimeout = 1;
	nid.uVersion = NOTIFYICON_VERSION_4;
	nid.dwInfoFlags = NIIF_INFO;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP ;   //������ӵ�е�״̬
	nid.uCallbackMessage = UM_ICONNOTIFY;            //�ص���Ϣ
	nid.hIcon = m_hIcon;                            //icon ����
	CString str = "�ƺ���.....";       //������ʾ
	lstrcpyn(nid.szTip, (LPCSTR)str, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
	Shell_NotifyIcon(NIM_ADD, &nid);   //��ʾ����
}

void CYellowButterflyDlg::ShowMsg(WPARAM wParam, LPARAM lParam)
{
	pMsg.Empty();
	pMsg = (char*)wParam;
	if (LoginReplyFlag == 1)
	{	
		Work = CreateThread(NULL, 0, RunTimeThread, UI_hwnd, NULL, NULL);
		ShowWindow(SW_HIDE);
		if (LoginTipFlags){
		CShowTip ShowTip;
		ShowTip.DoModal();
		}
	}
	else{
		if (lParam == 9)
		{
			if (IsLogin){ this->DoLogOut(); }
			if (IDYES == MessageBox(pMsg, " ��ܰ��ʾ", MB_YESNO))
			{
				this->OnBnClickedButtonLogin();
			}
			
		}
		else if (lParam == 1025)
		{
			if (IsLogin){ this->DoLogOut(); }
			this->OnBnClickedButtonLogin();
		}
		else
		{
			MessageBox(pMsg, " ��ܰ��ʾ", NULL);
			if (IsLogin){ this->DoLogOut(); }
		}

	}

}

void CYellowButterflyDlg::OnIconNotify(WPARAM wParam, LPARAM lParam)
{

	switch ((UINT)lParam)
	{
	case WM_RBUTTONDOWN: // click right button, show menu
	case WM_LBUTTONDOWN: // click or dbclick left button on icon
	case WM_LBUTTONDBLCLK: // should show desktop
		if (!IsWindowVisible())
		{
			this->ShowWindow(SW_SHOWNORMAL);
			this->SetActiveWindow();
			this->SetForegroundWindow();
			this->BringWindowToTop();

		}
		else
			ShowWindow(SW_HIDE);
		break;
	
		
	}
}

void  CYellowButterflyDlg::OnClose()
{
	CEXIT CExitDlg;
	CExitDlg.DoModal();

}

void CYellowButterflyDlg::LookThanks()
{
	CThanks ThanksDlg;
	ThanksDlg.DoModal();
}

void CYellowButterflyDlg::LookUsage()
{
	CUsage UsageDlg;
	UsageDlg.DoModal();
}

void CYellowButterflyDlg::EXEAutoStart()
{
	AfxMessageBox("�����������ܻ����ռ����Ҫ��Ҫ����!");
}

void CYellowButterflyDlg::DeleteNotify(WPARAM wParam, LPARAM lParam)
{
	if (IsLogin)
	{
		this->OnBnClickedButtonLogin();
	}
	TerminateThread(ListenThread, NULL);
	Sleep(50);
	CloseHandle(ListenThread);
	TerminateThread(iListenThread, NULL);
	Sleep(50);
	CloseHandle(iListenThread);
	free(Client); Client = NULL;
	Sleep(10);
	Shell_NotifyIcon(NIM_DELETE, &nid); //��������ɾ��ͼ�� 
	UpdateWindow();
	UpdateData();
	Sleep(100);
	exit(0);
}

void CYellowButterflyDlg::CloseYellowButterfly()
{
	PostQuitMessage(0);
}

LRESULT CYellowButterflyDlg::HideWindows(WPARAM wParam, LPARAM lParam)
{
	ShowWindow(SW_HIDE);
	return 1;
}

CString CYellowButterflyDlg::AutoGetIP()
{
	CString	 URL_HEADER("GET /ext_portal.magi?url=\"\"&radnum=\"1234\"&a.magi HTTP/1.1\r\n" \
		"User-Agent: GET_REAL_IP\r\n" \
		"Host: 1.1.1.1:8000\r\n\r\n");
	CString RESOLVE_STRING("wlanuserip="), resolve_string,ip;
	char recData[1024];
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	char Server_ip[16] = ("1.1.1.1"), UserIp[16] = {0};
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8000);
	serAddr.sin_addr.S_un.S_addr = inet_addr(Server_ip);
	connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr));
	send(sclient, URL_HEADER.GetBuffer(), URL_HEADER.GetLength(), 0);
	recv(sclient, recData, 1024, 0);
	closesocket(sclient);
	resolve_string = recData;
	int i = 0;
	int start = resolve_string.Find(RESOLVE_STRING) + RESOLVE_STRING.GetLength();
	int end = resolve_string.Find("&");
	while (start < end)
	{
		UserIp[i] = resolve_string.GetAt(start);
		i++; start++;
	}
	ip = UserIp;
	return ip;
}

DWORD WINAPI ListenBasThread(LPVOID pParam)
{
	SOCKET InfoSocket;
	Client = new UdpClient(&ClientSocket); //172.16.1.180
	Client->Initialize();
	Client->InitInfoSock(&InfoSocket);
	if (!Client->BindPort()){ ::MessageBeep(0); ::MessageBox((HWND)pParam, "3848�˿ڱ�ռ��,�����Ѿ�����һ�������ˣ�", "������ʾ", NULL); ::PostMessage((HWND)pParam, WM_DELETE_NOTIFY, NULL, NULL); }
	//Client->RecvData();
	while (ListenRunFlags)
	{	
		Client->Listen();
		Sleep(1);
	}
	Sleep(10);
	Client->~UdpClient();
	::closesocket(ClientSocket);
	::closesocket(InfoSocket);
	return 0;
}


DWORD WINAPI RunTimeThread(LPVOID pParam)
{
	CTime StartTime = CTime::GetCurrentTime();
	CString runtime;
	int KeepNum = 0;
	while (true)
	{
		Sleep(1000);
		KeepNum++; if (KeepNum >= 30){ KeepNum = 0; Client->SendHeartPack();}//MessageBox(NULL, "SendHeartPack", "tips:", NULL);
		CTime now = CTime::GetCurrentTime();
		CTimeSpan numSecond = now - StartTime;
		runtime.Format("����ʱ��: %dСʱ%d����%d��", numSecond.GetHours(), numSecond.GetMinutes(), numSecond.GetSeconds());
		::PostMessage((HWND)pParam, WM_UPDATE_RUN_TIME, (WPARAM)runtime.GetBuffer(), 0);
		
	}
	return 0;
}

DWORD WINAPI TimeCronThread(LPVOID pParam)
{
	long TotalSecond = (long)(Minute)* 60;
	CString runtime;
	runtime.Format("��ʱ%d������������ɣ�", Minute);
	HWND hwnd = ::FindWindow("YellowButterfly", NULL);
	while (true)
	{
		Sleep(30000);
		TotalSecond -= 30;
		if (TotalSecond <= 1)
		{
			::PostMessage(hwnd, WM_TIMECRONOVER, 0, 1);
			break;
		}
		else if ((TotalSecond % 60) == 0)
		{
			::PostMessage(hwnd, WM_TIMECRONOVER, (TotalSecond / 60), 0);
		}

	}
	AfxMessageBox(runtime);
	return 0;
}


DWORD WINAPI CheckNetThread(LPVOID pParam)
{
	int NetFlags = 0;
	char *TimeOut="���ӳ�ʱ����������!";
	while (true)
	{
		Sleep(10);
		if (IsConnectingFlag)
		{
			break;
		}
		if (NetFlags >= 600)
		{
			::PostMessage((HWND)pParam, WM_NOTIFYMSG, (WPARAM)TimeOut, 0);
			break;
		}
		NetFlags++;

	}
	return 0;
}

DWORD WINAPI ListenInfoThread(LPVOID pParam)
{
	while (ListenRunFlags)
	{
		Sleep(10);
		Client->Listen4999();
	}
	return 0;
}

void CYellowButterflyDlg::OnBnClickedCheckAutologin()
{
	CString FilePath = ::GetFilePath();
	FilePath += "Config.ini";
	if (AutoLogin)
	{
		AutoLogin = FALSE;
		::WritePrivateProfileString("�û�������Ϣ", "�Զ���¼", "No", FilePath);
	}
	else{
		AutoLogin = TRUE;
		::WritePrivateProfileString("�û�������Ϣ", "�Զ���¼", "Yes", FilePath);
	}
}


void CYellowButterflyDlg::OnBnClickedCheckRemember()
{
	CString FilePath = ::GetFilePath();
	FilePath += "Config.ini";
	if (RememberPasswd)
	{
		RememberPasswd = FALSE;
		::WritePrivateProfileString("�û�������Ϣ", "��ס����", "No", FilePath);
	}
	else{
		RememberPasswd = TRUE;
		::WritePrivateProfileString("�û�������Ϣ", "��ס����", "Yes", FilePath);
	}
}
void CYellowButterflyDlg::OnBnClickedCheckRelogin()
{
	CString FilePath = ::GetFilePath();
	FilePath += "Config.ini";
	if (ReLoginFlags)
	{
		ReLoginFlags = FALSE;
		::WritePrivateProfileString("�û�������Ϣ", "��������", "No", FilePath);
	}
	else{
		ReLoginFlags = TRUE;
		::WritePrivateProfileString("�û�������Ϣ", "��������", "Yes", FilePath);
	}
}

void CYellowButterflyDlg::OnBnClickedCheckLogintip()
{
	CString FilePath = ::GetFilePath();
	FilePath += "Config.ini";
	if (LoginTipFlags)
	{
		LoginTipFlags = FALSE;
		::WritePrivateProfileString("�û�������Ϣ", "��¼��ʾ", "No", FilePath);
	}
	else{
		LoginTipFlags = TRUE;
		::WritePrivateProfileString("�û�������Ϣ", "��¼��ʾ", "Yes", FilePath);
	}
}

void CYellowButterflyDlg::OnBnClickedButtonTimercron()
{
	if (IsLogin)
	{
	 if (TimeCronFlags)
	 {
		this->SetTimeCronThreaad();
		
	 }
	 else{
		this->SetTimeCronThreaad();
		
	     }
	}
	else{
		AfxMessageBox("��ĺ�����û��¼��!");
	}
}

void CYellowButterflyDlg::SetTimeCronThreaad()
{
	if (TimeCronFlags)
	{
		GetDlgItem(IDC_BUTTON_TimerCron)->SetWindowTextA("��ʱ��ʼ");
		GetDlgItem(IDC_EDIT_HOWMINUTE)->EnableWindow(TimeCronFlags);
		TimeCronFlags = FALSE;
		TerminateThread(hTimerCronThread, NULL);
		Sleep(50);
		CloseHandle(hTimerCronThread);
		Minute = 0;
	}
	else{
		CString HowMinute;
		GetDlgItem(IDC_EDIT_HOWMINUTE)->GetWindowTextA(HowMinute);
	 Minute = (int)atoi(HowMinute);
		if (Minute > 1){
			GetDlgItem(IDC_BUTTON_TimerCron)->SetWindowTextA("ȡ����ʱ");
			GetDlgItem(IDC_EDIT_HOWMINUTE)->EnableWindow(TimeCronFlags);
			TimeCronFlags = TRUE;
			hTimerCronThread = CreateThread(NULL, NULL, TimeCronThread, NULL, NULL, NULL);
			Sleep(100);
		}
		else{
			AfxMessageBox("��ʱ�����������1����!");
		}
		
	}
}

LRESULT CYellowButterflyDlg::TimeCron(WPARAM wParam, LPARAM lParam)
{
	CString HowTime;
	HowTime.Format("%d",(long)wParam);
	if (lParam == 1 && IsLogin)
	{
		Minute = 0;
		LoginReplyFlag = 0;
		this->DoLogOut();
		Client->SendLogoutPack();
		GetDlgItem(IDC_BUTTON_TimerCron)->SetWindowTextA("��ʱ��ʼ");
		GetDlgItem(IDC_EDIT_HOWMINUTE)->EnableWindow(TimeCronFlags);
		TimeCronFlags = FALSE;
	}
	else if (lParam == 0 && (long)wParam == 300)
	{
		AfxMessageBox("����5�����Զ�����!����ȡ�������ü�...");
	}
	GetDlgItem(IDC_EDIT_HOWMINUTE)->SetWindowTextA(HowTime);
	return 0;
}






