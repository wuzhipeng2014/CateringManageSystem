#pragma once


// AssignTable �Ի���

class AssignTable : public CDialogEx
{
	DECLARE_DYNAMIC(AssignTable)

public:
	AssignTable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AssignTable();

// �Ի�������
	enum { IDD = IDD_DIALOG_AssignTable };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
