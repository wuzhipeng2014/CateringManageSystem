
// MyDalgTest.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MyDalgTest.h"
#include "MyDalgTestDlg.h"
#include "Zhucedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDalgTestApp

BEGIN_MESSAGE_MAP(CMyDalgTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_COMMAND(IDM_SatffMange, &CMyDalgTestApp::OnSatffmange)
END_MESSAGE_MAP()


// CMyDalgTestApp ����

CMyDalgTestApp::CMyDalgTestApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMyDalgTestApp ����

CMyDalgTestApp theApp;


// CMyDalgTestApp ��ʼ��

BOOL CMyDalgTestApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	HRESULT hr;
	try
	{
		::CoInitialize(NULL);
		m_PConn = _ConnectionPtr(__uuidof(Connection));
		m_PConn->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=E:\\VS����\\C++ project\\MyDalgTest\\MyDalgTest\\juxian.accdb";
		m_PConn->Open("", "", "", adConnectUnspecified);
	}
	catch (_com_error e)
	{
		CString temp;
		temp += e.ErrorMessage();
		AfxMessageBox(temp);
		return false;
	}
#pragma region
		// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CMyDalgTestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
#pragma endregion

	//���ݿ�����
	
	



	return FALSE;
}



void CMyDalgTestApp::OnSatffmange()
{
	// TODO:  �ڴ���������������
	//MessageBox(_T("ע��Ա��"));
	//AfxMessageBox(_T("ע��Ա��"));
	CZhucedlg zhucedlg;
	zhucedlg.DoModal();

}
