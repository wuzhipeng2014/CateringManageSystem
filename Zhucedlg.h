#pragma once


// CZhucedlg �Ի���

class CZhucedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZhucedlg)

public:
	CZhucedlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CZhucedlg();
	_RecordsetPtr m_pRs;

// �Ի�������
	enum { IDD = IDD_DIALOG1 };
	CString m_Name;
	CString	m_pwd;
	CString m_Pwd2;
	_ConnectionPtr pConn;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCommti();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditPwd();
	afx_msg void OnEnChangeEditPwd2();
};
