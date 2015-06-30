// Checkout.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "Checkout.h"
#include "afxdialogex.h"


// Checkout 对话框

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
// Checkout 消息处理程序


BOOL Checkout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Checkout)), TRUE);
	//设置消费明细类表样式
	m_List_inventory.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_List_inventory.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_List_inventory.InsertColumn(1, _T("数量"), LVCFMT_LEFT, 100, 1);
	m_List_inventory.InsertColumn(2, _T("消费(元)"), LVCFMT_LEFT, 100, 1);

	//获取正在使用的餐桌号码
	CString sqlCommand("select * from tableUse where tableState='使用'");
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
	// 异常:  OCX 属性页应返回 FALSE
}


void Checkout::OnCbnSelchangeComboCheckoutTablenum()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	m_combo_TableNum.GetLBText(m_combo_TableNum.GetCurSel(), m_tableNum);
	CString sqlCommand("select * from paybill where 桌号=");
	sqlCommand += m_tableNum;
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	m_List_inventory.DeleteAllItems();

	int sum = 0, price;
	CString sPrice, sSum;
	CString dName, dCount;
	//将顾客的点菜清单添加到列表清单控件中
	while (!m_pRs->adoEOF)
	{
		sPrice = m_pRs->GetCollect("消费");
		price = _ttoi(sPrice);
		sum += price;
		dName = m_pRs->GetCollect("菜名");
		dCount = m_pRs->GetCollect("数量");
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString sReceived;
	m_Edit_Receive.GetWindowTextW(sReceived);
	m_Edit_Consume.GetWindowTextW(m_Consume);
	int change = _ttoi(sReceived) - _ttoi(m_Consume);
	CString sChanage;
	sChanage.Format(_T("%d"),change);
	m_Edit_change.SetWindowTextW(sChanage);
	// TODO:  在此添加控件通知处理程序代码
}


//将当前餐桌的使用状态改变为空闲，并将顾客的消费账单清空，
//然后将本次收入添加到日收入数据库中
void Checkout::OnBnClickedButtonCheckoutCheckout()
{
	// TODO:  在此添加控件通知处理程序代码
	//step1. 将餐桌使用情况改变
	m_combo_TableNum.GetWindowTextW(m_tableNum);
	if (m_tableNum.IsEmpty())
	{
		MessageBox(_T("请选择需要服务的桌号"));
		return;
	}
	CString sqlcommand ("select * from tableUse where tableID=");
	sqlcommand += m_tableNum;
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
	if (m_pRs->adoEOF)
	{
		MessageBox(_T("餐桌号码有误，请从新选择"));
		return;
	}
	CString tableState = m_pRs->GetCollect("tableState");

	if (tableState=="空闲")
	{
		MessageBox(_T("没有该餐桌的点餐信息"));
	}
	if (tableState=="使用")
	{
		CString sReceive;
		m_Edit_Receive.GetWindowTextW(sReceive);
		if (sReceive.IsEmpty())
		{
			MessageBox(_T("请输入顾客付款信息"));
			return;
		}
		CString sChange;
		m_Edit_change.GetWindowTextW(sChange);
		if (_ttoi(sChange)<0)
		{
			MessageBox(_T("付款金额不足，无法完成交易"));
			return;
		}
		else
		{

			//将此单交易金额写入日收入数据库

			//改变餐桌状态
			/*int tableNum = _ttoi(m_tableNum);*/
			sqlcommand = "update tableUse set tableState='空闲' where tableID=";
			
			sqlcommand += m_tableNum;
			theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
			m_combo_TableNum.DeleteString(m_combo_TableNum.GetCurSel());
			m_combo_TableNum.SetWindowTextW(_T(""));
		

			//将此单收入添加到日收入账单中
			CString consume, checkoutTime;
			CTime time = CTime::GetCurrentTime();
			checkoutTime = time.Format(_T("%Y-%m-%d"));
			//查看income表中是否有今天的收入记录，如果没有，添加记录
			sqlcommand = "select * from income where 时间='";
			sqlcommand += checkoutTime; sqlcommand += "'";
			m_pRs= theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
			m_Edit_Consume.GetWindowTextW(consume);
			if (m_pRs->adoEOF)
			{
				sqlcommand = "insert into income(日收入,时间) values( ";
				sqlcommand += consume; sqlcommand += ",'";
				sqlcommand += checkoutTime; sqlcommand += "')";
				theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);

			}
			else
			{
				
				sqlcommand = ("update income set 日收入=日收入+");
				sqlcommand += consume;
				sqlcommand += " where 时间='";
				sqlcommand += checkoutTime;
				sqlcommand += "'";
				theApp.m_PConn->Execute((_bstr_t)sqlcommand, NULL, adCmdText);
			}
			
			sqlcommand = "delete from paybill where 桌号= ";
			sqlcommand += m_tableNum;
			theApp.m_PConn->Execute((_bstr_t)sqlcommand,NULL,adCmdText);
			m_List_inventory.DeleteAllItems();
			m_Edit_change.SetWindowTextW(_T(""));
			m_Edit_Consume.SetWindowTextW(_T(""));
			m_Edit_Receive.SetWindowTextW(_T(""));
			MessageBox(_T("感谢光顾，欢迎再来"));
		}


	}
	UpdateData(false);
}


void Checkout::OnBnClickedButtonCheckoutback()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
