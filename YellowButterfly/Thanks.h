#pragma once
#include "resource.h"
class CThanks : public CDialogEx
{
public:
	CThanks();

	// 对话框数据
	enum { IDD = IDD_DIALOG_THANKS };
	//enum{ IDD = IDD_DIALOG_USAGE };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//CButton *pBtn = NULL;
	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OpenUrl(CString Url);

	afx_msg void OnBnClickedMfclinkNetshare();
	afx_msg void OnBnClickedMfclinkOpensise();
	afx_msg void OnBnClickedMfclinkMygithub();
	afx_msg void OnBnClickedMfclinkGetip();
};