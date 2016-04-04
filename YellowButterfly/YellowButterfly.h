
// YellowButterfly.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CYellowButterflyApp: 
// 有关此类的实现，请参阅 YellowButterfly.cpp
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

// 重写
public:
	virtual BOOL InitInstance();

// 实现

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