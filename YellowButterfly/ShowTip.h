#pragma once
#include "resource.h"
class CShowTip : public CDialogEx
{
public:
	CShowTip();

	// �Ի�������
	enum { IDD = IDD_DIALOG_TIPS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CButton *pBtn = NULL;
	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSure();

};

//CString pMsg;