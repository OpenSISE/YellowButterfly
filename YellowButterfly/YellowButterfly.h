
// YellowButterfly.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYellowButterflyApp: 
// �йش����ʵ�֣������ YellowButterfly.cpp
//
struct NetInfo{
	int port = 3848;
	CString ServerAddr;
	CString UserName;
	CString Password;
	CString Service;
	CString AdapterName;
	CString  LocalIp;
	CString StrMac;
	UCHAR Mac[6];
};
extern NetInfo LoginService;
//extern bool IsChangeMac;



class CYellowButterflyApp : public CWinApp
{
public:
	CYellowButterflyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYellowButterflyApp theApp;
extern BOOL ChangeAdapter;
extern CString pMsg;
extern unsigned int LoginReplyFlag;
extern BOOL IsConnectingFlag;
extern BOOL IsTroubleFlags;
extern BOOL ReLoginFlags;
extern BOOL LoginTipFlags;