// ChangeDish.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "ChangeDish.h"
#include "afxdialogex.h"



// ChangeDish �Ի���

IMPLEMENT_DYNAMIC(ChangeDish, CDialogEx)

ChangeDish::ChangeDish(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeDish::IDD, pParent)
{

}

ChangeDish::~ChangeDish()
{
}

void ChangeDish::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ChangeDish_CashInfo, m_List_CashInfo);
	DDX_Control(pDX, IDC_LIST_ChangeDish_OrderInfo, m_List_OrderInfo);
	DDX_Control(pDX, IDC_COMBO_ChangeDish_TableNumbers,m_Combo);
	DDX_Control(pDX, IDC_COMBO_ChangeDish_DishCount, m_Combo_DishCount);
	DDX_Text(pDX, IDC_COMBO_ChangeDish_DishCount, m_DishCount);
}


BEGIN_MESSAGE_MAP(ChangeDish, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ChangeDish_Add, &ChangeDish::OnBnClickedButtonChangedishAdd)
	ON_BN_CLICKED(IDC_BUTTON_ChangeDish_Minus, &ChangeDish::OnBnClickedButtonChangedishMinus)
	ON_BN_CLICKED(IDC_BUTTON_ChanngeIdshOK, &ChangeDish::OnBnClickedButtonChanngeidshok)
	ON_BN_CLICKED(IDC_BUTTON_ChangeDishCancel, &ChangeDish::OnBnClickedButtonChangedishcancel)
	ON_CBN_SELCHANGE(IDC_COMBO_ChangeDish_TableNumbers, &ChangeDish::OnCbnSelchangeComboChangedishTablenumbers)
	ON_CBN_SELCHANGE(IDC_COMBO_ChangeDish_DishCount, &ChangeDish::OnCbnSelchangeComboChangedishDishcount)
END_MESSAGE_MAP()


// ChangeDish ��Ϣ�������


//�����б������Ӳ�Ʒ��Ϣ
void ChangeDish::OnBnClickedButtonChangedishAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//step 1. �Ӳ����б��л�ȡѡ��Ĳ�Ʒ��Ϣ
	int index = m_List_CashInfo.GetSelectionMark();
	if (index != -1)
	{
		CString dName = m_List_CashInfo.GetItemText(index, 0);  //��ȡ�û�ѡ��Ĳ�Ʒ����
		m_List_OrderInfo.InsertItem(0, _T(""));
		m_List_OrderInfo.SetItemText(0,0,dName);
		OnCbnSelchangeComboChangedishDishcount();
		m_List_OrderInfo.SetItemText(0, 1, m_DishCount);
	}
	else
	{
		MessageBox(_T("��ѡ���Ʒ"));
	}

}

//�ӵ���б�ؼ����Ƴ����ֲ�Ʒ
void ChangeDish::OnBnClickedButtonChangedishMinus()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int index = m_List_OrderInfo.GetSelectionMark();
	if (index==-1)
	{
		MessageBox(_T("��ѡ���Ƴ��Ĳ�Ʒ"));
	}
	else
	{
		CString dName = m_List_OrderInfo.GetItemText(index,0);
		CString dCount = m_List_OrderInfo.GetItemText(index,1);
		int i_dCount = _ttoi(dCount);
		OnCbnSelchangeComboChangedishDishcount();
		int i_minusCount = _ttoi(m_DishCount);
		m_List_OrderInfo.DeleteItem(index);
		if (i_minusCount<i_dCount)  //���Ҫ�����ķ������ڻ�����Ѿ���ķ�����ֱ�ӽ�ѡ��Ĳ�Ʒ�Ƴ�����б�
		{
			int tmp = i_dCount - i_minusCount;
			dCount.Format(_T("%d"),tmp);
			m_List_OrderInfo.InsertItem(0,_T(""));
			m_List_OrderInfo.SetItemText(0, 0, dName);
			m_List_OrderInfo.SetItemText(0, 1, dCount);
		}
		

	}
}


//�Ӽ�����ɺ󣬽��û��ĵ����Ϣ��ӵ����ݿ���
//ͬʱ�����ݿ����û�ԭ���ĵ����Ϣɾ��
void ChangeDish::OnBnClickedButtonChanngeidshok()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	//step1.  ��ȡ�˿͵�������Ϣ
	CString tableNo;
	m_Combo.GetLBText(m_Combo.GetCurSel(), tableNo);
	if (!tableNo.IsEmpty())
	{
		int dishCount = m_List_OrderInfo.GetItemCount();
		if (dishCount==0)
		{
			MessageBox(_T("����"));
			return;
		}
		else //ɾ�����ݿ��д˹˿�ԭ�еĵ����Ϣ
		{
			CString sqlCommand("delete from paybill where ����=");
			sqlCommand += tableNo;
			theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);

			//���˿ͱ����ĵ����Ϣ��ӵ����ݿ�
			CString dName;
			CString dCount;
			CString dPrice;
			double totle = 0;
			CString sTotle;
			for (size_t i = 0; i < dishCount; i++)
			{
			 dName=	m_List_OrderInfo.GetItemText(i, 0);
			 dCount = m_List_OrderInfo.GetItemText(i, 1);
			 //��ȡ�˼���Ϣ
			 sqlCommand = "select * from caishInfo where ����='";
			 sqlCommand += dName; sqlCommand += "'";
			 m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
			 dPrice = m_pRs->GetCollect("�˼�");

			 totle = _ttoi(dPrice)*_ttoi(dCount);
			
			 sTotle.Format(_T("%lf"), totle);
			 sqlCommand = "insert into paybill (����,����,����,����) values (";
			 sqlCommand += tableNo; sqlCommand += ",'";
			 sqlCommand += dName; sqlCommand += "',";
			 sqlCommand += dCount; sqlCommand += ",";
			 sqlCommand += sTotle; sqlCommand += ")";

			 theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);

			}
			MessageBox(_T("��˳ɹ�"));
			CDialog::OnOK();
		}
	}
	else
	{
		MessageBox(_T("��ѡ������"));
		return;
	}

	//step2. 

}


void ChangeDish::OnBnClickedButtonChangedishcancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}

extern CMyDalgTestApp theApp;

BOOL ChangeDish::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List_CashInfo.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_List_CashInfo.InsertColumn(0, _T("����"), LVCFMT_LEFT, 100, 0);
	m_List_CashInfo.InsertColumn(1, _T("�˼�(Ԫ)"), LVCFMT_LEFT, 100, 1);
	CString sqlCommand ("select * from caishInfo ");
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	while (!m_pRs->adoEOF)
	{
		CString DName, DPrice;
		DName = m_pRs->GetCollect("����");
		DPrice = m_pRs->GetCollect("�˼�");
		m_List_CashInfo.InsertItem(0,_T(""));
		m_List_CashInfo.SetItemText(0,0,DName);
		m_List_CashInfo.SetItemText(0,1,DPrice);
		m_pRs->MoveNext();
	}

	//Ϊ�����������ʽ����
	m_List_OrderInfo.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_List_OrderInfo.InsertColumn(0,_T("����"),LVCFMT_LEFT,100,0);
	m_List_OrderInfo.InsertColumn(1,_T("����(��)"),LVCFMT_LEFT,100,1);
	sqlCommand = "select distinct ���� from paybill";





	//�������б��ؼ����������
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
	while (!m_pRs->adoEOF)
	{
		CString tableNo = m_pRs->GetCollect("����");
		m_Combo.AddString(tableNo);
		m_pRs->MoveNext();
	}

	//����ʾ��Ʒ�����������б�ؼ����������
	for (size_t i = 1; i < 15; i++)
	{
		CString tmp("");
		tmp.Format(_T("%d"),i);
		m_Combo_DishCount.AddString(tmp);
	}
	m_Combo_DishCount.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ChangeDish::OnCbnSelchangeComboChangedishTablenumbers()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//step 1. //��ȡ�����б��е�ǰ��ѡ�еĲ�����
	CString tableNo;
	m_Combo.GetLBText(m_Combo.GetCurSel(), tableNo);  
	//step 2. ��ȡ��ǰ�����Ѿ�����Ĳ�Ʒ��Ϣ
	CString sqlCommand("select  * from paybill where ����=");
	sqlCommand += tableNo;
	m_pRs= theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
	m_List_OrderInfo.DeleteAllItems();

	//step 3. ��ѯ���ò����ѵ�Ĳ�Ʒ��Ϣ��ӵ��б�ؼ���
	while (!m_pRs->adoEOF)
	{
		CString dName;
		CString dCount;
		dName = m_pRs->GetCollect("����");
		dCount = m_pRs->GetCollect("����");
		m_List_OrderInfo.InsertItem(0,_T(""));
		m_List_OrderInfo.SetItemText(0,0,dName);
		m_List_OrderInfo.SetItemText(0,1,dCount);
		m_pRs->MoveNext();

	}

}


void ChangeDish::OnCbnSelchangeComboChangedishDishcount()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_Combo_DishCount.GetWindowTextW(m_DishCount);
}
