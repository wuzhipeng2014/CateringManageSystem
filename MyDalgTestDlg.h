
// MyDalgTestDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"


// CMyDalgTestDlg �Ի���
class CMyDalgTestDlg : public CDialogEx
{
// ����
public:
	CMyDalgTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYDALGTEST_DIALOG };

	CImageList m_Imagelist;
	CStatusBar m_Statusbar;
	CToolBar m_Toolbar;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void ONDataresv();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSatffmange();
	afx_msg void OnLogin();
	afx_msg void OnAssigntable();
	afx_msg void OnButtonBackmainmunu();
	afx_msg void OnChangedishs();
	afx_msg void OnConsumerCheckout();
};
