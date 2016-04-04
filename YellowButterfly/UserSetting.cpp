// UserSetting.cpp : ʵ���ļ�
//




#include "stdafx.h"

#include "YellowButterfly.h"
#include "YellowButterflyDlg.h"
#include "UserSetting.h"
#include "afxdialogex.h"

//#pragma comment(lib,"CheckMacDll.dll")

User_AdapterInfo AdapterInfo[10] = { 0 };
//BOOL ChangeMac = FALSE;
BOOL AUTO_Flag;
CString User_IP;
CString IniFilePath;




void GetAdapter()
{
	BOOL UseLan = FALSE , UseWireless=FALSE;
	unsigned User_AdapterNum = 0; //��¼��������
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	PIP_ADAPTER_INFO pLanAdapterInfo = new IP_ADAPTER_INFO();
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	/*
	�����Ǽ����ж��Ƿ�Ķ���mac��ַdll�Ĵ��룬��Ҫ������ܵĿ�����ϵ��Ҫdll��Դ����....
	*/
	//typedef bool(*GetAddr)(char *);
	//GetAddr pFunc;
	//HINSTANCE hDllInst = LoadLibrary("CheckMacDll.dll");
	//if (hDllInst == NULL)
	//{
	//	FreeLibrary(hDllInst); AfxMessageBox("ȱ��CheckMacDll.dll�ļ�!"); exit(0);
	//}
	//pFunc = (GetAddr)GetProcAddress(hDllInst, "GetReallyMacAddress"); //  
	//if (!pFunc)
	//{
	//	FreeLibrary(hDllInst);
	//}
	//if (!IsTroubleFlags){
	//	IsTroubleFlags = FALSE;
	//}
	if (ERROR_SUCCESS == nRel)
	{
		while (pIpAdapterInfo)
		{
			CString temp,AdapterFlags;
			int DescriptionLen = strlen(pIpAdapterInfo->Description);
			for (int start = 0; start < 6; start++)
				temp += pIpAdapterInfo->Description[start];
			if (temp.CompareNoCase("VMware") == 0){ pIpAdapterInfo = pIpAdapterInfo->Next; continue; }

			if (memcmp(pIpAdapterInfo->IpAddressList.IpAddress.String,"0.0.0.0",16)!=0)
			{

			 for (int start = 0; start <DescriptionLen; start++)
			 {
				if (pIpAdapterInfo->Description[start] == 'P' || pIpAdapterInfo->Description[start] == 'p') {
					for (int j = start; j < (start + 4); j++) AdapterFlags += pIpAdapterInfo->Description[j];
					if (AdapterFlags.CompareNoCase("PCIe") == 0){ UseLan = TRUE;  pLanAdapterInfo = pIpAdapterInfo; }
				}
				else{
					continue;
				}
			 }
			 AdapterFlags.Empty();
			 for (int start = 0; start < DescriptionLen; start++)
			 {
				if (pIpAdapterInfo->Description[start] == 'W' || pIpAdapterInfo->Description[start] == 'w') {
					for (int j = start; j < (start + 8); j++) AdapterFlags += pIpAdapterInfo->Description[j];
					if (AdapterFlags.CompareNoCase("Wireless") == 0){ UseWireless = TRUE; } 
				}
				else{
					continue;
				}
			  }
			}
			memcpy(AdapterInfo[User_AdapterNum].Description, pIpAdapterInfo->Description, strlen(pIpAdapterInfo->Description));
			AdapterInfo[User_AdapterNum].User_IP_AddressInfo = &(pIpAdapterInfo->IpAddressList);
			//&& LoginService.AdapterName.IsEmpty()  //&& LoginService.AdapterName.IsEmpty()   / 
			if (UseLan && UseWireless)
			{
				LoginService.AdapterName = pLanAdapterInfo->Description;
				LoginService.LocalIp = pLanAdapterInfo->IpAddressList.IpAddress.String;
				memcpy(LoginService.Mac, pLanAdapterInfo->Address, 6);
				LoginService.Service = "internet";
				IsTroubleFlags = TRUE;
				AfxMessageBox("����������������������ͬʱ����������!\r\nΪ��֤��������������ò���Ҫ������!");
			}
			else if ((memcmp(pIpAdapterInfo->IpAddressList.IpAddress.String, "172.16", 6) == 0 || memcmp(pIpAdapterInfo->IpAddressList.IpAddress.String, "192.16", 6) == 0)   && !ChangeAdapter)
			{
				LoginService.AdapterName = pIpAdapterInfo->Description;
				LoginService.LocalIp = pIpAdapterInfo->IpAddressList.IpAddress.String;
				memcpy(LoginService.Mac, pIpAdapterInfo->Address, 6);
				LoginService.Service = "internet";
			}
			else if ((memcmp(pIpAdapterInfo->IpAddressList.IpAddress.String, "0.0.0.0", 16) != 0) && LoginService.AdapterName.IsEmpty() && !ChangeAdapter)
			{
				LoginService.AdapterName = pIpAdapterInfo->Description;
				LoginService.LocalIp = pIpAdapterInfo->IpAddressList.IpAddress.String;
				memcpy(LoginService.Mac, pIpAdapterInfo->Address, 6);
				LoginService.Service = "internet";
			}
			memcpy(AdapterInfo[User_AdapterNum].Mac, pIpAdapterInfo->Address,6);
			User_AdapterNum++;
			pIpAdapterInfo = pIpAdapterInfo->Next;
			//if (!IsChangeMac){   //�Ƿ�Ĺ�MAC��ַ��Ϊ�˸����Ի�����ȡ���������.......
			//IsChangeMac = pFunc(pIpAdapterInfo->AdapterName);
			//}
			//pIpAdapterInfo->AdapterName
			//
		}
		if (LoginService.AdapterName.IsEmpty())
		{
			AfxMessageBox("�޷��Զ�ѡ��������\r\r\n1.û�в������?\r\r\n2.û������Ҳû����WIFI?");
		}
	}
	/*FreeLibrary(hDllInst);*/

}



CString GetFilePath()
{
	CString FilePath;
	char Temp[64] = { 0 };
	::GetModuleFileName(NULL, Temp, sizeof(Temp));
	(strrchr(Temp, '\\'))[1] = 0;                     //��ȡ��ǰ�ļ�·��
	FilePath = Temp;
	FilePath.Replace("\\", "\\\\");
	return FilePath;
}


void CreateDefaultIni(CString FilePath, CString UserName , CString Password , CString LocalIp , CString LoginServer )
{
	
	WritePrivateProfileSection("�û�������Ϣ","�����ʺ�=\r\n��������=\r\n����ip=auto\r\n��֤������=172.16.1.180\r\n�������=internet\r\n��ס����=No\r\n�Զ���¼=No\r\n��¼��ʾ=Yes\r\n��������=No\r\n",FilePath);
}
// CUserSetting �Ի���

IMPLEMENT_DYNAMIC(CUserSetting, CDialogEx)

CUserSetting::CUserSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserSetting::IDD, pParent)
{
	
}

CUserSetting::~CUserSetting()
{
}

void CUserSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserSetting, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_AUTO, &CUserSetting::OnBnClickedCheckAuto)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, &CUserSetting::OnBnClickedButtonDefault)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUserSetting::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CUserSetting ��Ϣ�������

BOOL CUserSetting::OnInitDialog()
{
	IniFilePath = ::GetFilePath() + "Config.ini";
	this->LoadSetting();
	return true;
}

void CUserSetting::LoadSetting()
{
	GetAdapter();
	CString Strtemp;

	GetDlgItem(IDC_EDIT_REMOTE_SERVER)->SetWindowTextA("172.16.1.180");
	LoginType = (CComboBox*)GetDlgItem(IDC_COMBO_LOGINTYPE);
	LoginType->InsertString(0, "internet");
	LoginType->InsertString(1, "local");
	LoginType->SetCurSel(0);
	Adapter = (CComboBox*)GetDlgItem(IDC_COMBO_ADAPTER);
	int AdapterNum = 0;

	Strtemp = AdapterInfo[AdapterNum].Description;
	while (!Strtemp.IsEmpty())
	 {
		if (LoginService.AdapterName.CompareNoCase(AdapterInfo[AdapterNum].Description) == 0)
		{
			Adapter->InsertString(0, AdapterInfo[AdapterNum].Description); 
		}
		else{
			Adapter->InsertString(AdapterNum, AdapterInfo[AdapterNum].Description);
		}
		AdapterNum++; 
		Strtemp = AdapterInfo[AdapterNum].Description;
	}
	Adapter->SetCurSel(0);
	User_IP.Format("%s", AdapterInfo[Adapter->GetCurSel()].User_IP_AddressInfo->IpAddress.String);
	this->SetUserIp();

}

void CUserSetting::SetUserIp()
{
	//AUTO_Flag
	CString m_IP = LoadIni(LocalIpKey, IniFilePath);
	if (m_IP.CompareNoCase("auto") == 0){
		AUTO_Flag = TRUE;
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_AUTO);
		pBtn->SetCheck(true);
		GetDlgItem(IDC_IPADDRESS_USER)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_USER)->SetWindowTextA(User_IP);
	}
	else{
		AUTO_Flag = FALSE;
		GetDlgItem(IDC_IPADDRESS_USER)->SetWindowTextA(m_IP);
	}
}

void CUserSetting::OnBnClickedCheckAuto()
{
	if (AUTO_Flag)
	{
		AUTO_Flag = FALSE;
		GetDlgItem(IDC_IPADDRESS_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS_USER)->SetWindowTextA("172.16");
	}
	else{
		AUTO_Flag = TRUE;
		GetDlgItem(IDC_IPADDRESS_USER)->EnableWindow(FALSE);
		if (::LoadIni(LocalIpKey, IniFilePath).CompareNoCase(SetAutoValue) != 0){ User_IP = ::LoadIni(LocalIpKey, IniFilePath); }
		GetDlgItem(IDC_IPADDRESS_USER)->SetWindowTextA(User_IP);
	}

}


void CUserSetting::OnBnClickedButtonDefault()
{
	
	DeleteFile(IniFilePath);
	::CreateDefaultIni(IniFilePath);
	Adapter->ResetContent();
	this->LoadSetting();
	MessageBox("�ָ�Ĭ�����óɹ���"," ��ܰ��ʾ");
}


void CUserSetting::OnBnClickedButtonSave()
{
	CString INIContents, mUserName, mPasswd, mAutoLoad,mService,mServerIp,mAdapter,mRemember,mAutoLogin;
	Adapter->GetLBText(Adapter->GetCurSel(), mAdapter);
	SelectAdapter(mAdapter);
	GetDlgItem(IDC_EDIT_REMOTE_SERVER)->GetWindowTextA(mServerIp);
	AUTO_Flag ? mAutoLoad = "auto" : GetDlgItem(IDC_IPADDRESS_USER)->GetWindowTextA(mAutoLoad);
	mService = LoginType->GetCurSel() > 0 ? "local" : "internet"; 
	SetKeyValue("�û�������Ϣ", "����ip", mAutoLoad, IniFilePath);
	SetKeyValue("�û�������Ϣ", "��֤������", mServerIp, IniFilePath);
	SetKeyValue("�û�������Ϣ", "�������", mService, IniFilePath);
	MessageBox("���óɹ���", " ��ܰ��ʾ");
	PostMessage(WM_CLOSE, NULL, NULL);
}

void SelectAdapter(CString AdapterName)
{
	CString Adaptertemp;
	int AdapterNum = 0;
	Adaptertemp = AdapterInfo[AdapterNum].Description;
	while (!Adaptertemp.IsEmpty())
	{
		if (Adaptertemp.CompareNoCase(AdapterName) == 0)
		{
			LoginService.AdapterName = AdapterInfo[AdapterNum].Description;
			LoginService.LocalIp = AdapterInfo[AdapterNum].User_IP_AddressInfo->IpAddress.String;
			memcpy(LoginService.Mac,AdapterInfo[AdapterNum].Mac,6);
			ChangeAdapter = TRUE;
		}
		AdapterNum++;
		Adaptertemp = AdapterInfo[AdapterNum].Description;
	}

}

void SaveLogin(CString UserName, CString Password, BOOL PasswdFlag)
{
   CString FilePath1 = ::GetFilePath() + "Config.ini";
   SetKeyValue("�û�������Ϣ", "�����ʺ�", UserName,FilePath1);
   if (PasswdFlag){
	   SetKeyValue("�û�������Ϣ", "��������", Password, FilePath1);
   }
}



CString LoadIni(CString KeyName, CString FilePath)
{

	CString  Contents;
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

				if (strcmp(key, KeyName.GetBuffer())== 0){  
					Contents.Format("%s", data);
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
	return Contents;
}

void SetKeyValue(CString Section,CString Key,CString value,CString IniPath)
{
	::WritePrivateProfileString(Section,Key,value,IniPath);
}