#pragma once


// OrderDish 对话框

class OrderDish : public CDialogEx
{
	DECLARE_DYNAMIC(OrderDish)

public:
	OrderDish(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OrderDish();
	_RecordsetPtr m_pRs;
	CListCtrl m_recipeList;  //菜谱列表
	CListCtrl m_recipeOrderedList;  //点菜列表
	CComboBox m_combox;
	CString m_countOrder;
	CString m_tableNumber;

// 对话框数据
	enum { IDD = IDD_DIALOG_OrderDish };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOrderdishok();
	afx_msg void OnButtonOrderdishcancel();
	afx_msg void OnButtonAdddish();
	afx_msg void OnButtonMinusdish();
	afx_msg void OnCbnDropdownComboCount();
	afx_msg void OnCbnSelchangeComboCount();
	afx_msg void OnBnClickedButtonAdddish();
	afx_msg void OnBnClickedButtonOrderdishok();
	afx_msg void OnBnClickedButtonMinusdish();
	afx_msg void OnBnClickedButtonOrderdishcancel();
};
