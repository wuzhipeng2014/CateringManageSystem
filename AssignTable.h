#pragma once


// AssignTable 对话框

class AssignTable : public CDialogEx
{
	DECLARE_DYNAMIC(AssignTable)

public:
	AssignTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AssignTable();

// 对话框数据
	enum { IDD = IDD_DIALOG_AssignTable };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonBackmainmunu();
	virtual BOOL OnInitDialog();
	CListCtrl m_tableList;
	CString m_tableNumber;
	_RecordsetPtr m_pRs;
	afx_msg void OnDblclkListTableinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangedishs();
};
