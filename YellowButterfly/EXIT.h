#pragma once
#include "resource.h"
class CEXIT : public CDialogEx
{
public:
	CEXIT();

	// 对话框数据
	enum { IDD = IDD_DIALOG_EXIT };

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


