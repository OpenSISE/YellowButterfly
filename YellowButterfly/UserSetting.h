#pragma once
void GetAdapter();
CString GetFilePath();

void CreateDefaultIni(CString FilePath, CString UserName = "", CString Password = "", CString LocalIp = "", CString LoginServer = "172.16.1.180");
CString LoadIni(CString key,CString FilePath);
void SelectAdapter(CString);
void SaveLogin(CString UserName,CString Password,BOOL PasswdFlag=FALSE);
void SetKeyValue(CString Section, CString Key, CString value, CString IniPath);
// CUserSetting 对话框

class CUserSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CUserSetting)

public:
	CUserSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserSetting();

// 对话框数据
	enum { IDD = IDD_SETTING };
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	CString LocalIpKey = "本地ip";
	CString SetAutoValue = "auto";
	CString UserKey = "蝴蝶帐号";
	CString PasswdKey = "蝴蝶密码";
	CComboBox* LoginType;
	CComboBox* Adapter;
	CButton *pBtn = NULL;
	afx_msg void LoadSetting();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckAuto();
	afx_msg void SetUserIp();
	afx_msg void OnBnClickedButtonDefault();
	afx_msg void OnBnClickedButtonSave();

};

//extern BOOL ChangeMac;
