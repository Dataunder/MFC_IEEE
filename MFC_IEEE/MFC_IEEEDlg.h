
// MFC_IEEEDlg.h: 头文件
//

#pragma once


// CMFCIEEEDlg 对话框
class CMFCIEEEDlg : public CDialogEx
{
// 构造
public:
	CMFCIEEEDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_IEEE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit srcmac;
	CEdit desmac;
	CEdit data;
	afx_msg void OnBnClickedSubBut();
	afx_msg void OnBnClickedRefresh();
	CEdit res1;
	afx_msg void OnLvnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult);
	void fliter(CString sub[], CString tem);
	CString Transtype(CString tem);
	CString FCS(CString check, CString data);
	CString GetLen(CString tem);
	CString TransDatatoHex(CString tem);
	CString ShowHexdata(CString tem);
	CListCtrl res_list;
	CEdit Fcs;
	afx_msg void OnLvnItemchangedResList(NMHDR* pNMHDR, LRESULT* pResult);
};
