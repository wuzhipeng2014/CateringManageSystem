
// MyDalgTestDlg.h : 头文件
//

#pragma once
#include "resource.h"


// CMyDalgTestDlg 对话框
class CMyDalgTestDlg : public CDialogEx
{
// 构造
public:
	CMyDalgTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYDALGTEST_DIALOG };

	CImageList m_Imagelist;
	CStatusBar m_Statusbar;
	CToolBar m_Toolbar;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
