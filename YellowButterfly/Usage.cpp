#include "stdafx.h"
#include "Usage.h"
#include "afxdialogex.h"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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
	CString Usage="�ƺ���ֻ�Ǳ������Ķ���һ��С���ߣ�����Ҳûȥ������Ż���\r\n\
��˵�������Ծ��Ժã�Ҳû�оɰ��̺����ĵ���©����\r\n\
�ƺ���1.1�Ĺ��ܣ�\r\n\
���������ڿͻ��˵��������ܡ�\r\n\
1.�ƺ���������������ʵ�ǲ�����ô���õģ�Ĭ���Զ�ѡ�����������������еĻ���������ѡ�񲢱���ɣ�\r\n\
2.Ĭ��ѡ���Զ���ȡipģʽ�����ˣ�ֻҪ���������������Զ���ȡip��ϲ��diy�Ŀ����Լ���д��\r\n\
3.�ɹ�ѡ�Զ���¼��\r\n\
�ڿ������ö�ʱ����\r\n\
��������ֱ����д��ʱ�� ������  Ȼ����ʱ��ʼ��ť�Ϳ����ˣ�  ��Ҫȡ���͵�ȡ������ť��\r\n\
�ۿ��Թ�ѡ����������ʹ�ö����������ܼǵò�Ҫ��ѡ��½��ʾ...\r\n\
�ܵ�¼�ɹ�ѡ����ʾ��Ϣ\r\n";
	GetDlgItem(IDC_STATIC_USAGE)->SetWindowTextA(Usage);
	return true;
}