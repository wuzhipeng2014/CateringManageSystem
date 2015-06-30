// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "Login.h"
#include "afxdialogex.h"


// Login �Ի���

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
: CDialogEx(Login::IDD, pParent)
{
	m_Name = "";
	m_Pwd = "";
	tryCount = 0;
}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LoginName, m_Name);
	DDX_Text(pDX, IDC_EDIT_LoginPwd, m_Pwd);
	//DDX_Text(pDX,idc_edit_log ,m_Name);
	//DDX_Text(pDX,IDC_EDIT_Pwd,m_Pwd);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Login, &Login::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_Logout, &Login::OnBnClickedButtonLogout)
END_MESSAGE_MAP()


// Login ��Ϣ�������

extern CMyDalgTestApp theApp;
void Login::OnBnClickedButtonLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (!m_Name.IsEmpty() && !m_Pwd.IsEmpty())
	{
		CString sqlCommand("select * from login where Uname='");
		sqlCommand += m_Name;
		sqlCommand += "' and ";
		sqlCommand += "UPasswd='";
		sqlCommand += m_Pwd;
		sqlCommand += "'";
		m_pRst = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
		if (m_pRst->adoEOF)
		{
			AfxMessageBox(_T("�û������������"));
			m_Name.Empty();
			m_Pwd.Empty();
			tryCount++;
			UpdateData(false);
			if (tryCount==3)
			{
				CDialog::OnCancel();
			}
		}
		else
		{
			theApp.name = m_Name;
			theApp.pwd = m_Pwd;
			CDialog::OnOK();
			return;
		}
	}
	else
	{
		AfxMessageBox(_T("�û��������벻��Ϊ��"));
	}
}


void Login::OnBnClickedButtonLogout()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
