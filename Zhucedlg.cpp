// Zhucedlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "Zhucedlg.h"
#include "afxdialogex.h"

extern CMyDalgTestApp theApp;


// CZhucedlg �Ի���

IMPLEMENT_DYNAMIC(CZhucedlg, CDialogEx)

CZhucedlg::CZhucedlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZhucedlg::IDD, pParent)
{
	m_Name = _T("");
	m_pwd = _T("");
	m_Pwd2 = _T("");
	/*CoInitialize(NULL);
	pConn = _ConnectionPtr(__uuidof(Connection));
	pConn->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=E:\\VS����\\C++ project\\MyDalgTest\\MyDalgTest\\juxian.accdb";
	auto result = pConn->Open("", "", "", adConnectUnspecified);*/
}

CZhucedlg::~CZhucedlg()
{
}


//�˺�����ɴӱ༭���л�ȡ������ַ���
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


// CZhucedlg ��Ϣ�������

//ע������ύ��ť�����¼������¼�����鿴��ע����û�����
//���ݿ��еļ�¼�Ƿ��ظ�����ȷ����������������Ƿ���ͬ
//�ɹ��������ݿ����һ���û���¼
void CZhucedlg::OnBnClickedBtnCommti()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();  //��ʼ���Ի�������
	if (m_Name.IsEmpty()||m_pwd.IsEmpty()||m_Pwd2.IsEmpty())
	{
		AfxMessageBox(_T("�û��������벻��Ϊ��"));
		return;
	}
	if (m_pwd!=m_Pwd2)
	{
		AfxMessageBox(_T("��������벻һ��"));
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
		AfxMessageBox(_T("ע��ɹ�"));
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox(_T("���û����Ѿ�����"));
		return;
	}
#pragma endregion


}


void CZhucedlg::OnBnClickedBtnReset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_Name.Empty();
	m_pwd.Empty();
	m_Pwd2.Empty();
	UpdateData(false);
}


void CZhucedlg::OnEnChangeEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CZhucedlg::OnEnChangeEditPwd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CZhucedlg::OnEnChangeEditPwd2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
