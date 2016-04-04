#include "stdafx.h"
#include "Thanks.h"
#include "afxdialogex.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CThanks::CThanks() : CDialogEx(CThanks::IDD)
{
}


void CThanks::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CThanks, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_MFCLINK_NETSHARE, &CThanks::OnBnClickedMfclinkNetshare)
	ON_BN_CLICKED(IDC_MFCLINK_OPENSISE, &CThanks::OnBnClickedMfclinkOpensise)
	ON_BN_CLICKED(IDC_MFCLINK_MYGITHUB, &CThanks::OnBnClickedMfclinkMygithub)
	ON_BN_CLICKED(IDC_MFCLINK_GETIP, &CThanks::OnBnClickedMfclinkGetip)
END_MESSAGE_MAP()

BOOL CThanks::OnInitDialog()
{
	CDialog::OnInitDialog();
	return true;
}

void CThanks::OpenUrl(CString Url)
{

	
	ShellExecute(0, "open", Url.GetBuffer(), "", NULL, SW_SHOW);
}

void CThanks::OnBnClickedMfclinkNetshare()
{
	OpenUrl("https://github.com/xingrz/swiftz-protocal");
}


void CThanks::OnBnClickedMfclinkOpensise()
{
	OpenUrl("https://github.com/OpenSISE");
}


void CThanks::OnBnClickedMfclinkMygithub()
{
	OpenUrl("https://github.com/zhaobisheng");
}


void CThanks::OnBnClickedMfclinkGetip()
{
	OpenUrl("https://github.com/lcatro/supplicant_getadaptersinfo_dll");
}
