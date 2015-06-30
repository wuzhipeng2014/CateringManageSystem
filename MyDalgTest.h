
// MyDalgTest.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMyDalgTestApp: 
// 有关此类的实现，请参阅 MyDalgTest.cpp
//

class CMyDalgTestApp : public CWinApp
{
public:
	CMyDalgTestApp();
	CString name;
	CString pwd;


// 重写
public:
	virtual BOOL InitInstance();
	_ConnectionPtr m_PConn;

// 实现

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSatffmange();
};

extern CMyDalgTestApp theApp;