#pragma once
#include "resource.h"
class CThanks : public CDialogEx
{
public:
	CThanks();

	// �Ի�������
	enum { IDD = IDD_DIALOG_THANKS };
	//enum{ IDD = IDD_DIALOG_USAGE };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//CButton *pBtn = NULL;
	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OpenUrl(CString Url);

	afx_msg void OnBnClickedMfclinkNetshare();
	afx_msg void OnBnClickedMfclinkOpensise();
	afx_msg void OnBnClickedMfclinkMygithub();
	afx_msg void OnBnClickedMfclinkGetip();
};