#pragma once


// Checkout �Ի���

class Checkout : public CDialogEx
{
	DECLARE_DYNAMIC(Checkout)

public:
	Checkout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Checkout();
	_RecordsetPtr m_pRs;
	CString m_tableNum;
	CComboBox m_combo_TableNum;
	CListCtrl m_List_inventory;
	CEdit m_Edit_Consume;
	CEdit m_Edit_Receive;
	CEdit m_Edit_change;
	CString m_Consume;




// �Ի�������
	enum { IDD = IDD_DIALOG_Checkout };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboCheckoutTablenum();
	afx_msg void OnEnChangeEditCheckoutReceived();
	afx_msg void OnBnClickedButtonCheckoutCheckout();
	afx_msg void OnBnClickedButtonCheckoutback();
};
