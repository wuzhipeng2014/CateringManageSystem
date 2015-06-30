
// MyDalgTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "MyDalgTestDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Zhucedlg.h"
#include "AssignTable.h"
#include "ChangeDish.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSatffmange();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(IDM_SatffMange, &CAboutDlg::OnSatffmange)
END_MESSAGE_MAP()


// CMyDalgTestDlg 对话框



CMyDalgTestDlg::CMyDalgTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDalgTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDalgTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyDalgTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(9005, OnSatffmange)
	ON_COMMAND(9000, OnLogin)
	ON_COMMAND(9001, OnAssigntable)
	ON_COMMAND(9002, OnChangedishs)
	ON_COMMAND(9003, OnConsumerCheckout)
	ON_COMMAND(IDM_SatffMange, &CMyDalgTestDlg::OnSatffmange)
	ON_COMMAND(IDM_Login, &CMyDalgTestDlg::OnLogin)
	ON_COMMAND(IDM_AssignTable, &CMyDalgTestDlg::OnAssigntable)
	ON_COMMAND(IDC_BUTTON_BackMainMunu, &CMyDalgTestDlg::OnButtonBackmainmunu)
	ON_COMMAND(IDM_ChangeDishs, &CMyDalgTestDlg::OnChangedishs)
	ON_COMMAND(IDM_Consumer_Checkout, &CMyDalgTestDlg::OnConsumerCheckout)
END_MESSAGE_MAP()


// CMyDalgTestDlg 消息处理程序

BOOL CMyDalgTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	
	SetMenu(&menu);  //添加菜单栏
	menu.Detach();

	//添加工具栏
	m_Imagelist.Create(32, 32, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
	UINT Array[7];
	for (int i = 0; i<7; i++)
	{
		Array[i] = 9000 + i;
	}
	m_Toolbar.Create(this);
	m_Toolbar.SetButtons(Array, 7);
	m_Toolbar.SetButtonText(0, _T("系统登录"));
	m_Toolbar.SetButtonText(1, _T("开台"));
	m_Toolbar.SetButtonText(2, _T("加减菜"));
	m_Toolbar.SetButtonText(3, _T("顾客买单"));
	m_Toolbar.SetButtonText(4, _T("本日收入"));
	m_Toolbar.SetButtonText(5, _T("员工注册"));
	m_Toolbar.SetButtonText(6, _T("退出系统"));
	m_Toolbar.GetToolBarCtrl().SetButtonWidth(60, 120);
	m_Toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist);
	m_Toolbar.SetSizes(CSize(70, 60), CSize(28, 40));
	

	for ( int i = 0; i<4; i++)
	{
		Array[i] = 10000 + 1;
	}
	//此函数负责主窗口界面控件的重绘
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyDalgTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyDalgTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyDalgTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnSatffmange()
{
	// TODO:  在此添加命令处理程序代码
	//MessageBox(_T("员工注册"));
	//AfxMessageBox(_T("dlg员工注册"));
}

void CMyDalgTestDlg::ONDataresv()
{
	MessageBox(_T("工具栏按钮被点击"));
}

void CMyDalgTestDlg::OnSatffmange()
{
	//MessageBox(_T("对话框类中员工注册的响应事件"));
	// TODO:  在此添加命令处理程序代码
	CZhucedlg zhucedlg;
	zhucedlg.DoModal();
}

#include "Login.h"
void CMyDalgTestDlg::OnLogin()
{
	// TODO:  在此添加命令处理程序代码
	Login loginDlg;
	loginDlg.DoModal();
	
}


void CMyDalgTestDlg::OnAssigntable()
{
	// TODO:  在此添加命令处理程序代码
	AssignTable assingtable;
	assingtable.DoModal();
}


void CMyDalgTestDlg::OnButtonBackmainmunu()
{
	// TODO:  在此添加命令处理程序代码
	
}


void CMyDalgTestDlg::OnChangedishs()
{
	// TODO:  在此添加命令处理程序代码
	ChangeDish changeDish;
	changeDish.DoModal();
}

#include "Checkout.h"

void CMyDalgTestDlg::OnConsumerCheckout()
{
	// TODO:  在此添加命令处理程序代码
	Checkout checkout;
	checkout.DoModal();
}
