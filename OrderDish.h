#pragma once


// OrderDish �Ի���

class OrderDish : public CDialogEx
{
	DECLARE_DYNAMIC(OrderDish)

public:
	OrderDish(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~OrderDish();
	_RecordsetPtr m_pRs;
	CListCtrl m_recipeList;  //�����б�
	CListCtrl m_recipeOrderedList;  //����б�
	CComboBox m_combox;
	CString m_countOrder;
	CString m_tableNumber;

// �Ի�������
	enum { IDD = IDD_DIALOG_OrderDish };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
