// Checkout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "Checkout.h"
#include "afxdialogex.h"


// Checkout �Ի���

IMPLEMENT_DYNAMIC(Checkout, CDialogEx)


Checkout::Checkout(CWnd* pParent /*=NULL*/)
: CDialogEx(Checkout::IDD, pParent)
{

}

Checkout::~Checkout()
{
}

void Checkout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_Checkout_TableNum, m_combo_TableNum);
	DDX_Control(pDX, IDC_LIST_Checkout_Inventory, m_List_inventory);
	DDX_Control(pDX,IDC_EDIT_Checkout_Consume,m_Edit_Consume);
	DDX_Control(pDX,IDC_EDIT_Checkout_Received,m_Edit_Receive);
	DDX_Control(pDX, IDC_EDIT_Checkout_Change, m_Edit_change);
	//DDX_Text(pDX, IDC_COMBO_Checkout_TableNum, m_tableNum);
}


BEGIN_MESSAGE_MAP(Checkout, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_Checkout_TableNum, &Checkout::OnCbnSelchangeComboCheckoutTablenum)
	ON_EN_CHANGE(IDC_EDIT_Checkout_Received, &Checkout::OnEnChangeEditCheckoutReceived)
	ON_BN_CLICKED(IDC_BUTTON_Checkout_CheckOut, &Checkout::OnBnClickedButtonCheckoutCheckout)
	ON_BN_CLICKED(IDC_BUTTON_Checkout_back, &Checkout::OnBnClickedButtonCheckoutback)
END_MESSAGE_MAP()


extern CMyDalgTestApp theApp;
// Checkout ��Ϣ�������


BOOL Checkout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Checkout)), TRUE);
	//����������ϸ�����ʽ
	m_List_inventory.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_List_inventory.InsertColumn(0, _T("����"), LVCFMT_LEFT, 100, 0);
	m_List_inventory.InsertColumn(1, _T("����"), LVCFMT_LEFT, 100, 1);
	m_List_inventory.InsertColumn(2, _T("����(Ԫ)"), LVCFMT_LEFT, 100, 1);

	//��ȡ����ʹ�õĲ�������
	CString sqlCommand("select * from tableUse where tableState='ʹ��'");
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	int count = m_pRs->GetRecordCount();
	/*if (m_pRs->GetRecordCount()<1)
	{
	return true;
	}*/
	CString tNum;
	while (!m_pRs->adoEOF)
	{
		tNum = m_pRs->GetCollect("tableID");
		m_combo_TableNum.AddString(tNum);
		m_pRs->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Checkout::OnCbnSelchangeComboCheckoutTablenum()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_combo_TableNum.GetLBText(m_combo_TableNum.GetCurSel(), m_tableNum);
	CString sqlCommand("select * from paybill where ����=");
	sqlCommand += m_tableNum;
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	m_List_inventory.DeleteAllItems();

	int sum = 0, price;
	CString sPrice, sSum;
	CString dName, dCount;
	//���˿͵ĵ���嵥��ӵ��б��嵥�ؼ���
	while (!m_pRs->adoEOF)
	{
		sPrice = m_pRs->GetCollect("����");
		price = _ttoi(sPrice);
		sum += price;
		dName = m_pRs->GetCollect("����");
		dCount = m_pRs->GetCollect("����");
		m_List_inventory.InsertItem(0, _T(""));
		m_List_inventory.SetItemText(0, 0, dName);
		m_List_inventory.SetItemText(0, 1, dCount);
		m_List_inventory.SetItemText(0, 2, sPrice);
		m_pRs->MoveNext();
	}
	sSum.Format(_T("%d"),sum);
	m_Edit_Consume.SetWindowTextW(sSum);
	UpdateData(false);

}


void Checkout::OnEnChangeEditCheckoutReceived()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString sReceived;
	m_Edit_Receive.GetWindowTextW(sReceived);
	m_Edit_Consume.GetWindowTextW(m_Consume);
	int change = _ttoi(sReceived) - _ttoi(m_Consume);
	CString sChanage;
	sChanage.Format(_T("%d"),change);
	m_Edit_change.SetWindowTextW(sChanage);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//����ǰ������ʹ��״̬�ı�Ϊ���У������˿͵������˵���գ�
//Ȼ�󽫱���������ӵ����������ݿ���
void Checkout::OnBnClickedButtonCheckoutCheckout()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//step1. ������ʹ������ı�
	m_combo_TableNum.GetWindowTextW(m_tableNum);
	if (m_tableNum.IsEmpty())
	{
		MessageBox(_T("��ѡ����Ҫ���������"));
		return;
	}
	CString sqlcommand ("select * from tableUse where tableID=");
	sqlcommand += m_tableNum;
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
	if (m_pRs->adoEOF)
	{
		MessageBox(_T("�����������������ѡ��"));
		return;
	}
	CString tableState = m_pRs->GetCollect("tableState");

	if (tableState=="����")
	{
		MessageBox(_T("û�иò����ĵ����Ϣ"));
	}
	if (tableState=="ʹ��")
	{
		CString sReceive;
		m_Edit_Receive.GetWindowTextW(sReceive);
		if (sReceive.IsEmpty())
		{
			MessageBox(_T("������˿͸�����Ϣ"));
			return;
		}
		CString sChange;
		m_Edit_change.GetWindowTextW(sChange);
		if (_ttoi(sChange)<0)
		{
			MessageBox(_T("������㣬�޷���ɽ���"));
			return;
		}
		else
		{

			//���˵����׽��д�����������ݿ�

			//�ı����״̬
			/*int tableNum = _ttoi(m_tableNum);*/
			sqlcommand = "update tableUse set tableState='����' where tableID=";
			
			sqlcommand += m_tableNum;
			theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
			m_combo_TableNum.DeleteString(m_combo_TableNum.GetCurSel());
			m_combo_TableNum.SetWindowTextW(_T(""));
		

			//���˵�������ӵ��������˵���
			CString consume, checkoutTime;
			CTime time = CTime::GetCurrentTime();
			checkoutTime = time.Format(_T("%Y-%m-%d"));
			//�鿴income�����Ƿ��н���������¼�����û�У���Ӽ�¼
			sqlcommand = "select * from income where ʱ��='";
			sqlcommand += checkoutTime; sqlcommand += "'";
			m_pRs= theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
			m_Edit_Consume.GetWindowTextW(consume);
			if (m_pRs->adoEOF)
			{
				sqlcommand = "insert into income(������,ʱ��) values( ";
				sqlcommand += consume; sqlcommand += ",'";
				sqlcommand += checkoutTime; sqlcommand += "')";
				theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);

			}
			else
			{
				
				sqlcommand = ("update income set ������=������+");
				sqlcommand += consume;
				sqlcommand += " where ʱ��='";
				sqlcommand += checkoutTime;
				sqlcommand += "'";
				theApp.m_PConn->Execute((_bstr_t)sqlcommand, NULL, adCmdText);
			}
			
			sqlcommand = "delete from paybill where ����= ";
			sqlcommand += m_tableNum;
			theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
			m_List_inventory.DeleteAllItems();
			m_Edit_change.SetWindowTextW(_T(""));
			m_Edit_Consume.SetWindowTextW(_T(""));
			m_Edit_Receive.SetWindowTextW(_T(""));
			MessageBox(_T("��л��ˣ���ӭ����"));
		}


	}
	UpdateData(false);
}


void Checkout::OnBnClickedButtonCheckoutback()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
