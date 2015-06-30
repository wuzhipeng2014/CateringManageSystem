
// MyDalgTestDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyDalgTestDlg �Ի���



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


// CMyDalgTestDlg ��Ϣ�������

BOOL CMyDalgTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	
	SetMenu(&menu);  //��Ӳ˵���
	menu.Detach();

	//��ӹ�����
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
	m_Toolbar.SetButtonText(0, _T("ϵͳ��¼"));
	m_Toolbar.SetButtonText(1, _T("��̨"));
	m_Toolbar.SetButtonText(2, _T("�Ӽ���"));
	m_Toolbar.SetButtonText(3, _T("�˿���"));
	m_Toolbar.SetButtonText(4, _T("��������"));
	m_Toolbar.SetButtonText(5, _T("Ա��ע��"));
	m_Toolbar.SetButtonText(6, _T("�˳�ϵͳ"));
	m_Toolbar.GetToolBarCtrl().SetButtonWidth(60, 120);
	m_Toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist);
	m_Toolbar.SetSizes(CSize(70, 60), CSize(28, 40));
	

	for ( int i = 0; i<4; i++)
	{
		Array[i] = 10000 + 1;
	}
	//�˺������������ڽ���ؼ����ػ�
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyDalgTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyDalgTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnSatffmange()
{
	// TODO:  �ڴ���������������
	//MessageBox(_T("Ա��ע��"));
	//AfxMessageBox(_T("dlgԱ��ע��"));
}

void CMyDalgTestDlg::ONDataresv()
{
	MessageBox(_T("��������ť�����"));
}

void CMyDalgTestDlg::OnSatffmange()
{
	//MessageBox(_T("�Ի�������Ա��ע�����Ӧ�¼�"));
	// TODO:  �ڴ���������������
	CZhucedlg zhucedlg;
	zhucedlg.DoModal();
}

#include "Login.h"
void CMyDalgTestDlg::OnLogin()
{
	// TODO:  �ڴ���������������
	Login loginDlg;
	loginDlg.DoModal();
	
}


void CMyDalgTestDlg::OnAssigntable()
{
	// TODO:  �ڴ���������������
	AssignTable assingtable;
	assingtable.DoModal();
}


void CMyDalgTestDlg::OnButtonBackmainmunu()
{
	// TODO:  �ڴ���������������
	
}


void CMyDalgTestDlg::OnChangedishs()
{
	// TODO:  �ڴ���������������
	ChangeDish changeDish;
	changeDish.DoModal();
}

#include "Checkout.h"

void CMyDalgTestDlg::OnConsumerCheckout()
{
	// TODO:  �ڴ���������������
	Checkout checkout;
	checkout.DoModal();
}
