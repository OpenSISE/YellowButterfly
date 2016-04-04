#pragma once
#include "resource.h"
class CShowTip : public CDialogEx
{
public:
	CShowTip();

	// 对话框数据
	enum { IDD = IDD_DIALOG_TIPS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CButton *pBtn = NULL;
	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSure();

};

//CString pMsg;