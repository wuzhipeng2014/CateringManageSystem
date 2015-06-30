// ChangeDish.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "ChangeDish.h"
#include "afxdialogex.h"



// ChangeDish 对话框

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


// ChangeDish 消息处理程序


//向点菜列表框中添加菜品信息
void ChangeDish::OnBnClickedButtonChangedishAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	//step 1. 从菜谱列表中获取选择的菜品信息
	int index = m_List_CashInfo.GetSelectionMark();
	if (index != -1)
	{
		CString dName = m_List_CashInfo.GetItemText(index, 0);  //获取用户选择的菜品名称
		m_List_OrderInfo.InsertItem(0, _T(""));
		m_List_OrderInfo.SetItemText(0,0,dName);
		OnCbnSelchangeComboChangedishDishcount();
		m_List_OrderInfo.SetItemText(0, 1, m_DishCount);
	}
	else
	{
		MessageBox(_T("请选择菜品"));
	}

}

//从点菜列表控件中移除部分菜品
void ChangeDish::OnBnClickedButtonChangedishMinus()
{
	// TODO:  在此添加控件通知处理程序代码
	int index = m_List_OrderInfo.GetSelectionMark();
	if (index==-1)
	{
		MessageBox(_T("请选择移除的菜品"));
	}
	else
	{
		CString dName = m_List_OrderInfo.GetItemText(index,0);
		CString dCount = m_List_OrderInfo.GetItemText(index,1);
		int i_dCount = _ttoi(dCount);
		OnCbnSelchangeComboChangedishDishcount();
		int i_minusCount = _ttoi(m_DishCount);
		m_List_OrderInfo.DeleteItem(index);
		if (i_minusCount<i_dCount)  //如果要减掉的分数大于或等于已经点的分数，直接将选择的菜品移除点菜列表
		{
			int tmp = i_dCount - i_minusCount;
			dCount.Format(_T("%d"),tmp);
			m_List_OrderInfo.InsertItem(0,_T(""));
			m_List_OrderInfo.SetItemText(0, 0, dName);
			m_List_OrderInfo.SetItemText(0, 1, dCount);
		}
		

	}
}


//加减菜完成后，将用户的点菜信息添加到数据库中
//同时将数据库中用户原来的点菜信息删除
void ChangeDish::OnBnClickedButtonChanngeidshok()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	//step1.  获取顾客的桌号信息
	CString tableNo;
	m_Combo.GetLBText(m_Combo.GetCurSel(), tableNo);
	if (!tableNo.IsEmpty())
	{
		int dishCount = m_List_OrderInfo.GetItemCount();
		if (dishCount==0)
		{
			MessageBox(_T("请点菜"));
			return;
		}
		else //删除数据库中此顾客原有的点菜信息
		{
			CString sqlCommand("delete from paybill where 桌号=");
			sqlCommand += tableNo;
			theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);

			//将顾客变更后的点菜信息添加到数据库
			CString dName;
			CString dCount;
			CString dPrice;
			double totle = 0;
			CString sTotle;
			for (size_t i = 0; i < dishCount; i++)
			{
			 dName=	m_List_OrderInfo.GetItemText(i, 0);
			 dCount = m_List_OrderInfo.GetItemText(i, 1);
			 //获取菜价信息
			 sqlCommand = "select * from caishInfo where 菜名='";
			 sqlCommand += dName; sqlCommand += "'";
			 m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
			 dPrice = m_pRs->GetCollect("菜价");

			 totle = _ttoi(dPrice)*_ttoi(dCount);
			
			 sTotle.Format(_T("%lf"), totle);
			 sqlCommand = "insert into paybill (桌号,菜名,数量,消费) values (";
			 sqlCommand += tableNo; sqlCommand += ",'";
			 sqlCommand += dName; sqlCommand += "',";
			 sqlCommand += dCount; sqlCommand += ",";
			 sqlCommand += sTotle; sqlCommand += ")";

			 theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);

			}
			MessageBox(_T("点菜成功"));
			CDialog::OnOK();
		}
	}
	else
	{
		MessageBox(_T("请选择桌号"));
		return;
	}

	//step2. 

}


void ChangeDish::OnBnClickedButtonChangedishcancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}

extern CMyDalgTestApp theApp;

BOOL ChangeDish::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List_CashInfo.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_List_CashInfo.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_List_CashInfo.InsertColumn(1, _T("菜价(元)"), LVCFMT_LEFT, 100, 1);
	CString sqlCommand ("select * from caishInfo ");
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	while (!m_pRs->adoEOF)
	{
		CString DName, DPrice;
		DName = m_pRs->GetCollect("菜名");
		DPrice = m_pRs->GetCollect("菜价");
		m_List_CashInfo.InsertItem(0,_T(""));
		m_List_CashInfo.SetItemText(0,0,DName);
		m_List_CashInfo.SetItemText(0,1,DPrice);
		m_pRs->MoveNext();
	}

	//为点菜类表进行样式设置
	m_List_OrderInfo.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_List_OrderInfo.InsertColumn(0,_T("菜名"),LVCFMT_LEFT,100,0);
	m_List_OrderInfo.InsertColumn(1,_T("数量(份)"),LVCFMT_LEFT,100,1);
	sqlCommand = "select distinct 桌号 from paybill";





	//向下拉列表框控件中添加数据
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
	while (!m_pRs->adoEOF)
	{
		CString tableNo = m_pRs->GetCollect("桌号");
		m_Combo.AddString(tableNo);
		m_pRs->MoveNext();
	}

	//向显示菜品数量的下拉列表控件中添加数据
	for (size_t i = 1; i < 15; i++)
	{
		CString tmp("");
		tmp.Format(_T("%d"),i);
		m_Combo_DishCount.AddString(tmp);
	}
	m_Combo_DishCount.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ChangeDish::OnCbnSelchangeComboChangedishTablenumbers()
{
	// TODO:  在此添加控件通知处理程序代码
	//step 1. //获取下拉列表中当前被选中的餐桌号
	CString tableNo;
	m_Combo.GetLBText(m_Combo.GetCurSel(), tableNo);  
	//step 2. 获取当前餐桌已经点过的菜品信息
	CString sqlCommand("select  * from paybill where 桌号=");
	sqlCommand += tableNo;
	m_pRs= theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
	m_List_OrderInfo.DeleteAllItems();

	//step 3. 查询将该餐桌已点的菜品信息添加到列表控件中
	while (!m_pRs->adoEOF)
	{
		CString dName;
		CString dCount;
		dName = m_pRs->GetCollect("菜名");
		dCount = m_pRs->GetCollect("数量");
		m_List_OrderInfo.InsertItem(0,_T(""));
		m_List_OrderInfo.SetItemText(0,0,dName);
		m_List_OrderInfo.SetItemText(0,1,dCount);
		m_pRs->MoveNext();

	}

}


void ChangeDish::OnCbnSelchangeComboChangedishDishcount()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Combo_DishCount.GetWindowTextW(m_DishCount);
}
