// Zhucedlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "Zhucedlg.h"
#include "afxdialogex.h"

extern CMyDalgTestApp theApp;


// CZhucedlg 对话框

IMPLEMENT_DYNAMIC(CZhucedlg, CDialogEx)

CZhucedlg::CZhucedlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZhucedlg::IDD, pParent)
{
	m_Name = _T("");
	m_pwd = _T("");
	m_Pwd2 = _T("");
	/*CoInitialize(NULL);
	pConn = _ConnectionPtr(__uuidof(Connection));
	pConn->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=E:\\VS程序\\C++ project\\MyDalgTest\\MyDalgTest\\juxian.accdb";
	auto result = pConn->Open("", "", "", adConnectUnspecified);*/
}

CZhucedlg::~CZhucedlg()
{
}


//此函数完成从编辑框中获取输入的字符串
void CZhucedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_Name,m_Name);
	DDX_Text(pDX,IDC_EDIT_Pwd,m_pwd);
	DDX_Text(pDX,IDC_EDIT_Pwd2,m_Pwd2);
}


BEGIN_MESSAGE_MAP(CZhucedlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_Commti, &CZhucedlg::OnBnClickedBtnCommti)
	ON_BN_CLICKED(IDC_BTN_Reset, &CZhucedlg::OnBnClickedBtnReset)
	ON_EN_CHANGE(IDC_EDIT_Name, &CZhucedlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_Pwd, &CZhucedlg::OnEnChangeEditPwd)
	ON_EN_CHANGE(IDC_EDIT_Pwd2, &CZhucedlg::OnEnChangeEditPwd2)
END_MESSAGE_MAP()


// CZhucedlg 消息处理程序

//注册界面提交按钮单击事件，该事件负责查看待注册的用户名与
//数据库中的记录是否重复，并确定两次输入的密码是否相同
//成功后向数据库添加一条用户记录
void CZhucedlg::OnBnClickedBtnCommti()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();  //初始化对话框数据
	if (m_Name.IsEmpty()||m_pwd.IsEmpty()||m_Pwd2.IsEmpty())
	{
		AfxMessageBox(_T("用户名或密码不能为空"));
		return;
	}
	if (m_pwd!=m_Pwd2)
	{
		AfxMessageBox(_T("输入的密码不一致"));
		return;
	}

	//CoInitialize(NULL);

	//_RecordsetPtr pRst(__uuidof(Recordset));
	//pRst = pConn->Execute("select * from login", NULL, adCmdText);
	//while (!pRst->adoEOF)
	//{
	//	auto re=pRst->GetCollect("Uname");
	//	AfxMessageBox((_bstr_t)re);
	//	/*AfxMessageBox( );*/
	//	pRst->MoveNext();
	//}
	//CoUninitialize();

#pragma region
	CString sqlCommand;
	sqlCommand += "select * from login where Uname= '";
	sqlCommand += m_Name;
	sqlCommand += "'";
	CoInitialize(NULL);
	_RecordsetPtr pRst(__uuidof(Recordset));
	pRst= theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	/*while (!pRst->adoEOF)
	{
		AfxMessageBox(pRst->GetCollect("Uname"));
		pRst->MoveNext();
	}*/
	//pRst=	theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	if (pRst->adoEOF)
	{
		sqlCommand.Empty();
		sqlCommand = "insert into login (Uname,UPasswd,power) values ('";
		sqlCommand+=m_Name;
		sqlCommand += "',\'";
		sqlCommand += m_pwd;
		sqlCommand += "',2)";
		
		theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
		AfxMessageBox(_T("注册成功"));
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox(_T("该用户名已经存在"));
		return;
	}
#pragma endregion


}


void CZhucedlg::OnBnClickedBtnReset()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Name.Empty();
	m_pwd.Empty();
	m_Pwd2.Empty();
	UpdateData(false);
}


void CZhucedlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CZhucedlg::OnEnChangeEditPwd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CZhucedlg::OnEnChangeEditPwd2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
