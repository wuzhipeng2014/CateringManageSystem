// OrderDish.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "OrderDish.h"
#include "afxdialogex.h"
#include <string>


// OrderDish �Ի���

IMPLEMENT_DYNAMIC(OrderDish, CDialogEx)

OrderDish::OrderDish(CWnd* pParent /*=NULL*/)
: CDialogEx(OrderDish::IDD, pParent)
{
	m_countOrder = "1";
}

OrderDish::~OrderDish()
{
}

void OrderDish::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Recipe, m_recipeList);
	DDX_Control(pDX, IDC_LIST_RecipeOrdered, m_recipeOrderedList);
	DDX_Control(pDX, IDC_COMBO_Count, m_combox);
	
	DDX_Text(pDX, IDC_EDIT_OrderDish_TableNumber, m_tableNumber);
	/*DDX_Text(pDX, IDC_COMBO_Count, m_countOrder);*/

}


BEGIN_MESSAGE_MAP(OrderDish, CDialogEx)
	ON_COMMAND(IDC_BUTTON_OrderDishOk, &OrderDish::OnButtonOrderdishok)
	ON_COMMAND(IDC_BUTTON_OrderDishCancel, &OrderDish::OnButtonOrderdishcancel)
	ON_COMMAND(IDC_BUTTON_AddDish, &OrderDish::OnButtonAdddish)
	ON_COMMAND(IDC_BUTTON_MinusDish, &OrderDish::OnButtonMinusdish)
	ON_CBN_DROPDOWN(IDC_COMBO_Count, &OrderDish::OnCbnDropdownComboCount)
	ON_CBN_SELCHANGE(IDC_COMBO_Count, &OrderDish::OnCbnSelchangeComboCount)
	ON_BN_CLICKED(IDC_BUTTON_AddDish, &OrderDish::OnBnClickedButtonAdddish)
	ON_BN_CLICKED(IDC_BUTTON_OrderDishOk, &OrderDish::OnBnClickedButtonOrderdishok)
	ON_BN_CLICKED(IDC_BUTTON_MinusDish, &OrderDish::OnBnClickedButtonMinusdish)
	ON_BN_CLICKED(IDC_BUTTON_OrderDishCancel, &OrderDish::OnBnClickedButtonOrderdishcancel)
END_MESSAGE_MAP()


// OrderDish ��Ϣ�������

extern CMyDalgTestApp theApp;

BOOL OrderDish::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3)), TRUE);
	m_recipeList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_recipeList.InsertColumn(0, _T("����"), LVCFMT_LEFT, 140, 0);
	m_recipeList.InsertColumn(1, _T("���� (��/Ԫ)"), LVCFMT_LEFT, 140, 1);
	m_recipeOrderedList.InsertColumn(0, _T("����"), LVCFMT_LEFT, 140, 0);
	m_recipeOrderedList.InsertColumn(1, _T("�������ݣ�"), LVCFMT_LEFT, 140, 1);
	CString sqlCommand("select * from caishInfo");
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	int index = 0;
	while (!m_pRs->adoEOF)
	{
		CString tID = m_pRs->GetCollect("����");
		CString TSta = m_pRs->GetCollect("�˼�");
		m_recipeList.InsertItem(index, tID);
		m_recipeList.SetItemText(index, 0, tID);
		m_recipeList.SetItemText(index, 1, TSta);
		m_pRs->MoveNext();

	}

	m_combox.AddString(_T("1"));
	m_combox.AddString(_T("2"));
	m_combox.AddString(_T("3"));
	m_combox.AddString(_T("4"));
	m_combox.AddString(_T("5"));
	m_combox.AddString(_T("6"));
	m_combox.AddString(_T("7"));
	m_combox.AddString(_T("8"));
	m_combox.AddString(_T("9"));
	m_combox.AddString(_T("10"));
	m_combox.AddString(_T("11"));
	m_combox.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//�����ɣ����ȷ����ť�����ݴ洢�����ݿ��У�
void OrderDish::OnButtonOrderdishok()
{
	// TODO:  �ڴ���������������
	//MessageBox(_T("ȷ��"));
	UpdateData();
	CString sqlCommand;
	int countNumbers = m_recipeOrderedList.GetItemCount();
	if (countNumbers == 0)
	{
		AfxMessageBox(_T("����"));
		return;
	}
	sqlCommand = "update tableUse set tableState='ʹ��' where tableID=";
	sqlCommand += m_tableNumber;
	theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);


	CString OrderList(""), dishName(""), dishNumbers(""),unitCost,totalCost;
	//���˵������Ϣ��ӵ����ݿ��
#pragma region
	for (size_t i = 0; i < countNumbers; i++)
	{
		dishName = m_recipeOrderedList.GetItemText(i,0);  //����
		dishNumbers = m_recipeOrderedList.GetItemText(i,1); //����
		sqlCommand = "select * from caishInfo where ����='";
		sqlCommand += dishName;
		sqlCommand += "'";

		m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
		unitCost= m_pRs->GetCollect("�˼�");
		
		char * puc = (char *)unitCost.GetBuffer(unitCost.GetLength());
		totalCost =(char *)(_bstr_t)( _ttof(unitCost)*_ttof(dishNumbers));
		//totalCost = (char*)(_bstr_t)(atof(puc)*atof((char *)dishNumbers.GetBuffer(dishNumbers.GetLength())));
		//%%%%%%%%%%%�˴���дsql���Ӧ��ע����Ӣ�ķ��ŵ��л�
		sqlCommand = "insert into paybill(����,����,����,����) values('";
		sqlCommand += m_tableNumber;
		sqlCommand += "','";
		sqlCommand += dishName; sqlCommand += "','";
		sqlCommand += dishNumbers; sqlCommand += "','";
		sqlCommand += totalCost; sqlCommand += "')";
		//sqlCommand = "insert into paybill(����,����,����,����) values('6601','��������',1,30)";
		theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
	}

	
#pragma endregion
	MessageBox(_T("�˶����ѱ�ϵͳ���գ����Ժ�"));
	CDialog::OnOK();
}


void OrderDish::OnButtonOrderdishcancel()
{
	// TODO:  �ڴ���������������
	MessageBox(_T("ȡ��"));
}


void OrderDish::OnButtonAdddish()
{
	// TODO:  �ڴ���������������
	/*MessageBox(_T("����"));*/
	int index = m_recipeList.GetSelectionMark();
	if (index != -1)
	{
		CString str = m_recipeList.GetItemText(index, 0);
		m_recipeOrderedList.InsertItem(0, _T(""));
		m_recipeOrderedList.SetItemText(0, 0, str);
		OnCbnSelchangeComboCount();
		m_recipeOrderedList.SetItemText(0, 1, m_countOrder);
	}
	else
	{
		MessageBox(_T("��ѡ�����"));
	}


}


void OrderDish::OnButtonMinusdish()
{
	// TODO:  �ڴ���������������
	/*MessageBox(_T("����"));*/
	m_recipeOrderedList.DeleteItem(m_recipeOrderedList.GetSelectionMark());
}


void OrderDish::OnCbnDropdownComboCount()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*MessageBox(_T("combox"));*/

	CString std;

}


void OrderDish::OnCbnSelchangeComboCount()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_combox.GetWindowTextW(m_countOrder);
}


void OrderDish::OnBnClickedButtonAdddish()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void OrderDish::OnBnClickedButtonOrderdishok()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void OrderDish::OnBnClickedButtonMinusdish()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void OrderDish::OnBnClickedButtonOrderdishcancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
