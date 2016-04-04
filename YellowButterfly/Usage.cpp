#include "stdafx.h"
#include "Usage.h"
#include "afxdialogex.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CUsage::CUsage() : CDialogEx(CUsage::IDD)
{
}


void CUsage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CUsage, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CUsage::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString Usage="黄蝴蝶只是本人无聊恶搞的一个小工具，代码也没去精简和优化，\r\n\
但说到兼容性绝对好，也没有旧版绿蝴蝶的盗号漏洞。\r\n\
黄蝴蝶1.1的功能：\r\n\
①正常安腾客户端的上网功能。\r\n\
1.黄蝴蝶的上网配置其实是不用怎么设置的，默认自动选择内网的网卡，不行的话，请自行选择并保存吧！\r\n\
2.默认选择自动获取ip模式就行了，只要能连接内网就能自动获取ip。喜欢diy的可以自己填写。\r\n\
3.可勾选自动登录。\r\n\
②可以设置定时断网\r\n\
在主界面直接填写定时的 分钟数  然后点计时开始按钮就可以了！  需要取消就点取消任务按钮！\r\n\
③可以勾选断网重连，使用断网重连功能记得不要勾选登陆提示...\r\n\
④登录可勾选不提示消息\r\n";
	GetDlgItem(IDC_STATIC_USAGE)->SetWindowTextA(Usage);
	return true;
}