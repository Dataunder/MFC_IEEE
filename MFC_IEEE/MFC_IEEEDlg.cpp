
// MFC_IEEEDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_IEEE.h"
#include "MFC_IEEEDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif





int clicktime = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCIEEEDlg 对话框



CMFCIEEEDlg::CMFCIEEEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_IEEE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCIEEEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_MAC, srcmac);
	DDX_Control(pDX, IDC_DES_MAC, desmac);
	DDX_Control(pDX, IDC_DATA_EDIT, data);
	DDX_Control(pDX, IDC_RESULT_1, res1);
	DDX_Control(pDX, IDC_RES_LIST, res_list);
}

BEGIN_MESSAGE_MAP(CMFCIEEEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUB_BUT, &CMFCIEEEDlg::OnBnClickedSubBut)
	ON_BN_CLICKED(IDC_REFRESH, &CMFCIEEEDlg::OnBnClickedRefresh)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST5, &CMFCIEEEDlg::OnLvnItemchangedList5)
END_MESSAGE_MAP()


// CMFCIEEEDlg 消息处理程序

BOOL CMFCIEEEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CRect rect;
	res_list.GetClientRect(&rect);

	res_list.SetExtendedStyle(res_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	res_list.InsertColumn(0, _T("前导码"), LVCFMT_CENTER, rect.Width() / 2, 0);
	res_list.InsertColumn(1, _T("帧前定界符"), LVCFMT_CENTER, rect.Width() / 4, 1);
	res_list.InsertColumn(2, _T("目的地址"), LVCFMT_CENTER, rect.Width() / 3, 2);
	res_list.InsertColumn(3, _T("源地址"), LVCFMT_CENTER, rect.Width() / 3, 3);
	res_list.InsertColumn(4, _T("长度字段"), LVCFMT_CENTER, rect.Width() / 2, 4);
	res_list.InsertColumn(5, _T("数据字段"), LVCFMT_CENTER, rect.Width()*2, 5);
	res_list.InsertColumn(6, _T("校验字段"), LVCFMT_CENTER, rect.Width() / 4, 6);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCIEEEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCIEEEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCIEEEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCIEEEDlg::OnBnClickedSubBut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1;
	srcmac.GetWindowText(str1);		//获取输入框源mac

	CString str2;
	desmac.GetWindowText(str2);		//获取输入框目的mac

	CString str3;
	data.GetWindowText(str3);		//获取输入框data数据

	int lh = str3.GetLength();
	char teml[30];

	sprintf(teml, "0x%04X", lh);

	CString srcstr[6];
	CString desstr[6];
	fliter(srcstr, str1);
	fliter(desstr, str2);

	CString data1;
	data1 = ShowHexdata(str3);



	CString len;
	len = GetLen(str3);

	CString smac,dmac,temp1,temp2;

	for (int i = 0; i < 6; i++)
	{
		temp1 += srcstr[i];
		temp2 += desstr[i];
	}
	
	smac = Transtype(temp1);
	dmac = Transtype(temp2);
	

	CString data;
	data = TransDatatoHex(str3);

	CString data2;
	data2 = Transtype(data);

	CString IEEE;
	IEEE = smac + dmac + len + data2;

	CString check = "100000111";

	CString fcs = FCS(IEEE, check);

	IEEE += fcs;


	res_list.InsertItem(clicktime, _T("aa aa aa aa aa aa aa "));
	res_list.SetItemText(clicktime, 1, _T("ab "));
	res_list.SetItemText(clicktime, 2, _T(srcstr[0] +' '+ srcstr[1] + ' ' + srcstr[2] + ' ' + srcstr[3] + ' ' + srcstr[4] + ' ' + srcstr[5]));
	res_list.SetItemText(clicktime, 3, _T(desstr[0] +' '+ desstr[1] + ' ' + desstr[2] + ' ' + desstr[3] + ' ' + desstr[4] + ' ' + desstr[5]));
	res_list.SetItemText(clicktime, 4, _T(teml));
	res_list.SetItemText(clicktime, 5, _T(data1));
	res_list.SetItemText(clicktime, 6, _T(fcs));


	res1.SetWindowTextA(fcs);

	clicktime++;
}


void CMFCIEEEDlg::OnBnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
}



//将输入的mac格式转化为实际的mac地址
void CMFCIEEEDlg::fliter(CString sub[], CString tem)
{
	

	int temp1 = tem.Find('-');
	int temp2 = tem.Find('-', temp1 + 1);	//找到字符串中第二个出现'-'的索引
	int temp3 = tem.Find('-', temp2 + 1);	//找到字符串中第三个出现'-'的索引
	int temp4 = tem.Find('-', temp3 + 1);	//找到字符串中第4个出现'-'的索引
	int temp5 = tem.Find('-', temp4 + 1);	//找到字符串中第5个出现'-'的索引


	sub[0] = tem.Mid(0, temp1);
	sub[1] = tem.Mid(temp1 + 1, temp2 - temp1 - 1);
	sub[2] = tem.Mid(temp2 + 1, temp3 - temp2 - 1);
	sub[3] = tem.Mid(temp3 + 1, temp4 - temp3 - 1);
	sub[4] = tem.Mid(temp4 + 1, temp5 - temp4 - 1);
	sub[5] = tem.Mid(tem.ReverseFind('-')+1, tem.GetLength()- tem.ReverseFind('-')-1);


}

//使选中的LISTBOX具有反馈机制
void CMFCIEEEDlg::OnLvnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString strLangName;    // 选择语言的名称字符串   
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		strLangName = res_list.GetItemText(pNMListView->iItem, 0);
		// 将选择的语言显示与编辑框中   
		SetDlgItemText(IDC_RES_LIST, strLangName);
	}
}

//将16进制串转换为2进制串
CString CMFCIEEEDlg::Transtype(CString data)
{
	CString tem;
	for (int i = 0; i < data.GetLength(); i++)
	{
		int a = data.GetAt(i);
		//将字符型转化为整型
		if (a>='0'&&a<='9'||a>='a'&&a<='f'||a>='A'&&a<='F')
		{
			if (a >= '0' && a <= '9')
			{
				a = a - 48;
			}

			if (a >= 'a' && a <= 'f')
			{
				a = a - 87;
			}

			if (a >= 'A' && a <= 'F')
			{
				a = a - 55;
			}
		}
		//进制转换代码，数组b存储转换后的长度为4位的数据
		int b[4];
		for (int j = 0; j < 4; j++)
		{
			b[j] = a % 2;
			a = a / 2;
		}

		for (int k = 3; k >= 0; k--)
		{
			if (b[k] == 0)
			{
				tem += "0";
			}

			else
				tem += "1";

		}

	}
	return tem;//返回转换后的二进制字符串
}
//获取数据字段的长度
CString  CMFCIEEEDlg::GetLen(CString tem)
{
	CString length;
	long len = tem.GetLength();
	if (len>1500)
	{
		MessageBox("请输入1500字符长度以内的数据");
		data.SetFocus();
	}
	else
	{
		//把数据字段长度转换位两个字节
		for (int i = 0; i < 16; i++)
		{
			if (len % 2 == 0)
			{
				length = "0"+ length;			
				len = len / 2;
			}

			else if(len % 2 == 1)
			{
				length = "1"+ length;
				len = len / 2;
			}
		}
	}

	return length;
}

CString CMFCIEEEDlg::TransDatatoHex(CString tem)
{
	CString data;
	for (int i = 0; i < tem.GetLength(); i++)
	{
		char temp1[20];
		int temp = tem.GetAt(i);
		sprintf(temp1, "%x", temp);
		data = data + temp1;
	}

	return data;
}

CString CMFCIEEEDlg::ShowHexdata(CString tem)
{
	CString data;
	for (int i = 0; i < tem.GetLength(); i++)
	{
		char temp1[20];
		int temp = tem.GetAt(i);
		sprintf(temp1, "%x ", temp);
		data = data + temp1;
	}

	return data;
}


//Fcs校验算法
//data为算法中的被除数，check为除数;
CString CMFCIEEEDlg::FCS(CString data, CString check)
{

	for (int i = 0; i < check.GetLength()-1; i++)//根据除数长度，在被除数后面添0；
	{
		data += "0";
	}
	
	int m[10000],n[10000];//用于存储将字符串转化成int类型的数据的data和check中的数据
	int md = data.GetLength();
	int nc = check.GetLength();
	//将data中的字符转换为int类型存储
	for (int i = 0; i < md; i++)
	{
		if (data.GetAt(i)=='0')
		{
			m[i] = 0;
		}

		else if (data.GetAt(i) == '1')
		{
			m[i] = 1;
		}
	}//将check中的字符转换为int类型存储

	for (int i = 0; i < nc; i++)
	{
		if (check.GetAt(i) == '0')
		{
			n[i] = 0;
		}

		else if (check.GetAt(i) == '1')
		{
			n[i] = 1;
		}
	}

	int d[10000];
	//异或运算，将m[i]中的数据进行运算更换，最终结果的后nc-1位即为计算得出的FCS
	for (int i = 0; i <md-nc+1; i++)
	{
		d[i] = m[i];
		for (int j = 1; j < nc; j++)
		{
			if (m[i] == 0)
			{
				m[j + i] = !m[j + i] & 0 | m[j + i] & 1;
			}
			else  m[j + i] = !m[j + i] & n[j] | m[j + i] & !n[j];
		}
	}
	CString abc = "";//用于存储计算得到的FCS
	for (int i = md - nc + 1; i < md; i++)
	{
		if (m[i] == 0)
			abc += "0";
		else if (m[i] == 1)
			abc += "1";
	}
	int dc = abc.GetLength();//得到FCS序列的长度  不足8位就添0，即得到一个字节的数据
	if (abc.GetLength() < 8)
	{
		for (int i = 0; i < 8 - dc; i++)
		{
			abc = abc + "0";
		}
	}
	CString ba = "";
	for (int i = 0; i < abc.GetLength(); i++) {
		if (abc.GetAt(i) == '0')
			ba += "0";
		else ba += "1";
		if ((i + 1) % 8 == 0)
			ba += "";
	}

	return ba;//返回长度为一个字节的FCS

}