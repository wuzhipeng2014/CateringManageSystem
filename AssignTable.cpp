// AssignTable.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "AssignTable.h"
#include "afxdialogex.h"


extern CMyDalgTestApp theApp;

// AssignTable 对话框

IMPLEMENT_DYNAMIC(AssignTable, CDialogEx)

AssignTable::AssignTable(CWnd* pParent /*=NULL*/)
	: CDialogEx(AssignTable::IDD, pParent)
{

}

AssignTable::~AssignTable()
{
}

void AssignTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LIST_TableInfo,m_tableList);
	DDX_Text(pDX, IDC_EDIT_AssignTableNumber, m_tableNumber);
}


BEGIN_MESSAGE_MAP(AssignTable, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &AssignTable::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_BackMainMunu, &AssignTable::OnBnClickedButtonBackmainmunu)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TableInfo, &AssignTable::OnDblclkListTableinfo)
	ON_COMMAND(IDM_ChangeDishs, &AssignTable::OnChangedishs)
END_MESSAGE_MAP()


// AssignTable 消息处理程序


#include "OrderDish.h"
void AssignTable::OnBnClickedButtonOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_tableNumber.IsEmpty())
		AfxMessageBox(_T("请选择桌号"));
	else
	{
		CString sqlCommand ("select * from tableUse where tableID= ");
		sqlCommand += m_tableNumber;
		sqlCommand += " and tableState='空闲'";
		m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand,NULL,adCmdText);
		if (m_pRs->adoEOF)
		{
			CString sWarn = m_tableNumber + "有人了";
			AfxMessageBox(sWarn);
			m_tableNumber.Empty();
			UpdateData(false);
			return;
		}
		else
		{
			/*MessageBox(_T("点菜"));*/
			//跳转到点菜页面
			OrderDish orderDishDlg;
			orderDishDlg.m_tableNumber = m_tableNumber;
			orderDishDlg.DoModal();
			m_pRs = NULL;
			CDialog::OnOK();
		}
		

	}
}


void AssignTable::OnBnClickedButtonBackmainmunu()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


BOOL AssignTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2)),TRUE);
	m_tableList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_tableList.InsertColumn(0, _T("桌号"), LVCFMT_LEFT, 140, 0);
	m_tableList.InsertColumn(1,_T("状态"), LVCFMT_LEFT,140,1);
	CString sqlCommand ("select * from tableUse");
	m_pRs = theApp.m_PConn->Execute((_bstr_t)sqlCommand, NULL, adCmdText);
	int index = 0;
	while (!m_pRs->adoEOF)
	{
		CString tID = m_pRs->GetCollect("tableID");
		CString TSta = m_pRs->GetCollect("tableState");
		m_tableList.InsertItem(index,_T(""));
		m_tableList.SetItemText(index, 0, tID);
		m_tableList.SetItemText(index,1,TSta);
		m_pRs->MoveNext();

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void AssignTable::OnDblclkListTableinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	str = m_tableList.GetItemText(m_tableList.GetSelectionMark(), 0);
	m_tableNumber = str;
	UpdateData(false);

	*pResult = 0;
}


void AssignTable::OnChangedishs()
{
	// TODO:  在此添加命令处理程序代码
}
