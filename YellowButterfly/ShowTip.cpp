#include "stdafx.h"
#include "ShowTip.h"
#include "afxdialogex.h"
//#include "bSocket.h"
#include "YellowButterfly.h"
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���




CShowTip::CShowTip() : CDialogEx(CShowTip::IDD)
{

}

void CShowTip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CShowTip, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CShowTip::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect TipRect;
	GetClientRect(&TipRect);//
	int x = GetSystemMetrics(SM_CXSCREEN);//��ȡӫĻ����Ŀ�ȣ���λΪ����  
	int y = GetSystemMetrics(SM_CYSCREEN);//��ȡӫĻ����ĸ߶ȣ���λΪ����  
	TipRect.left = x - TipRect.Width() - 1;
	TipRect.top = y - TipRect.Height() - 66;
	TipRect.right = x-1;
	TipRect.bottom = y - 1;
	MoveWindow(TipRect);
	GetDlgItem(IDC_STATIC_NEWS)->SetWindowTextA(pMsg);
	//PostMessage(WM_CLOSE, NULL, NULL);
	return true;
}