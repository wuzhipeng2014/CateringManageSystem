#pragma once


// Login �Ի���

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Login();

// �Ի�������
	enum { IDD = IDD_DIALOG_Login };
	CString m_Name;
	CString m_Pwd;
	_RecordsetPtr m_pRst;
	int tryCount;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
};
