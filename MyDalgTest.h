
// MyDalgTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyDalgTestApp: 
// �йش����ʵ�֣������ MyDalgTest.cpp
//

class CMyDalgTestApp : public CWinApp
{
public:
	CMyDalgTestApp();
	CString name;
	CString pwd;


// ��д
public:
	virtual BOOL InitInstance();
	_ConnectionPtr m_PConn;

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSatffmange();
};

extern CMyDalgTestApp theApp;