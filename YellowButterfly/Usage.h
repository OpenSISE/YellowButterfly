#pragma once
#include "resource.h"
class CUsage : public CDialogEx
{
public:
	CUsage();

	// �Ի�������
	//enum { IDD = IDD_DIALOG_THANKS };
	enum{ IDD = IDD_DIALOG_USAGE };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()


};