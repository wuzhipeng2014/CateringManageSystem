#pragma once


// ChangeDish �Ի���

class ChangeDish : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeDish)

public:
	ChangeDish(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangeDish();
	CListCtrl m_List_CashInfo;
	CListCtrl m_List_OrderInfo;
	CComboBox m_Combo;
	CComboBox m_Combo_DishCount;
	_RecordsetPtr m_pRs;
	CString m_DishCount;
// �Ի�������
	enum { IDD = IDD_DIALOG_ChangeDish };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChangedishAdd();
	afx_msg void OnBnClickedButtonChangedishMinus();
	afx_msg void OnBnClickedButtonChanngeidshok();
	afx_msg void OnBnClickedButtonChangedishcancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboChangedishTablenumbers();
	afx_msg void OnCbnSelchangeComboChangedishDishcount();
};
