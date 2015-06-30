#pragma once


// CZhucedlg 对话框

class CZhucedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZhucedlg)

public:
	CZhucedlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CZhucedlg();
	_RecordsetPtr m_pRs;

// 对话框数据
	enum { IDD = IDD_DIALOG1 };
	CString m_Name;
	CString	m_pwd;
	CString m_Pwd2;
	_ConnectionPtr pConn;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCommti();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditPwd();
	afx_msg void OnEnChangeEditPwd2();
};
