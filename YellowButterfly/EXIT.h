#pragma once
#include "resource.h"
class CEXIT : public CDialogEx
{
public:
	CEXIT();

	// �Ի�������
	enum { IDD = IDD_DIALOG_EXIT };

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


