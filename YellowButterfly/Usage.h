#pragma once
#include "resource.h"
class CUsage : public CDialogEx
{
public:
	CUsage();

	// 对话框数据
	//enum { IDD = IDD_DIALOG_THANKS };
	enum{ IDD = IDD_DIALOG_USAGE };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()


};