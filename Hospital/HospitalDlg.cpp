
// HospitalDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Hospital.h"
#include "HospitalDlg.h"
#include "afxdialogex.h"
#include "Error.h"
#include "Record.h"
#include "Diary.h"
#include "Information.h"
#include <fstream>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define EW 23
#define WIDTH 760
#define HEIGHT 520
#define FILENAME "input.txt"
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

static UINT indicators[] = { IDS_INDICATOR_TIME };

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


// CHospitalDlg 对话框


int check(string st)
{
	int i, l = st.size();
	if (l != 8)
		return -1;
	for (i = 0; i < l; i++)
		if ((st[i] < '0') || (st[i] > '9'))
			return -1;
	return 0;
}

CHospitalDlg::CHospitalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	int i, j, k;
	for (i = 0; i < NUM_ROOM;i++)
		for (j = 0; j < NUM_DOCTOR; j++)
		{
			head[i][j] = 0;
			tail[i][j] = -1;
			for (k = 0; k < NUM_MAX; k++)
			{
				c[i][j][k].name = "";
				c[i][j][k].guahao_time = "--------------------";
				c[i][j][k].start_time = "--------------------";
				c[i][j][k].end_time = "--------------------";
				c[i][j][k].bc = false;
			}
		}
	for (i = 0; i < NUM_BROOM; i++)
		for (j = 0; j < NUM_BMAC; j++)
		{
			bhead[i][j] = 0;
			btail[i][j] = -1;
			for (k = 0; k < NUM_MAX; k++)
			{
				l[i][j][k].name = "";
				l[i][j][k].guahao_time = "--------------------";
				l[i][j][k].start_time = "--------------------";
				l[i][j][k].end_time = "--------------------";
				l[i][j][k].bc = false;
			}
		}	
	loading = 0;
}

void CHospitalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, Clist);
}

BEGIN_MESSAGE_MAP(CHospitalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CHospitalDlg::OnLvnItemchangedList2)
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CHospitalDlg::OnNMDblclkList2)
	ON_COMMAND_RANGE(ID_32784, ID_32785, GET)
	ON_COMMAND_RANGE(ID_32786, ID_32830, GUA)
	ON_COMMAND_RANGE(ID_32831, ID_32875, DOE)
	ON_COMMAND_RANGE(ID_32876, ID_32878, DOD)
	ON_COMMAND_RANGE(ID_32879, ID_32923, QUE)
	ON_COMMAND_RANGE(ID_32924, ID_32926, BUE)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI_RANGE(ID_32831, ID_32875, NDOE)
	ON_UPDATE_COMMAND_UI_RANGE(ID_32876, ID_32878, NDOD)
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()


// CHospitalDlg 消息处理程序

BOOL CHospitalDlg::OnInitDialog()
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

	CMenu m_Menu;
	CString st;
	int i, j, w;
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);
	bar.Create(this);
	bar.SetIndicators(indicators, 1);
	bar.SetPaneInfo(0, IDS_INDICATOR_TIME, SBPS_STRETCH, 20);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDS_INDICATOR_TIME);
	CTime t;
	t = CTime::GetCurrentTime();
	bar.SetPaneText(0, t.Format("当前时间 : %H:%M:%S"));
	SetTimer(1, 1000, NULL);
	CRect rect;
	GetClientRect(&rect);
	MoveWindow(0, 0, WIDTH, HEIGHT);
	Clist.MoveWindow(0, 0, rect.Width(), rect.Height() - 20);
	// 获取编程语言列表视图控件的位置和大小   
	Clist.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	Clist.SetExtendedStyle(Clist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	w = int(rect.Width()) - EW;
	// 为列表视图控件添加三列   
	Clist.InsertColumn(0, _T("科室/诊间"), LVCFMT_CENTER, w / 4, 0);
	Clist.InsertColumn(1, _T("当值医生"), LVCFMT_CENTER, w / 4, 1);
	Clist.InsertColumn(2, _T("当前就诊"), LVCFMT_CENTER, w / 4, 2);
	Clist.InsertColumn(3, _T("准备就诊"), LVCFMT_CENTER, w - 3 * w / 4, 3);
	// 在列表视图控件中插入列表项，并设置列表子项文本   
	for (i = 0; i < NUM_ROOM; i++)
		for (j = 0; j < NUM_DOCTOR; j++)
		{
			st.Format(_T("%d诊间"), j + 1);
			st = CA2T(room[i].c_str()) + st;
			Clist.InsertItem(i * NUM_DOCTOR + j, st);
			Clist.SetItemText(i * NUM_DOCTOR + j, 1, CA2T(doctor[i * NUM_DOCTOR + j].c_str()));
			Clist.SetItemText(i * NUM_DOCTOR + j, 2, _T("无"));
			Clist.SetItemText(i * NUM_DOCTOR + j, 3, _T("无"));
		}
	for (i = 0; i < NUM_BROOM; i++)
		for (j = 0; j < NUM_BMAC; j++)
		{
			st.Format(_T("%d号机位"), j + 1);
			st = CA2T(broom[i].c_str()) + st;
			Clist.InsertItem(NUM_ROOM * NUM_DOCTOR + i * NUM_BMAC + j, st);
			Clist.SetItemText(NUM_ROOM * NUM_DOCTOR + i * NUM_BMAC + j, 1, CA2T(bmac[i * NUM_BMAC + j].c_str()));
			Clist.SetItemText(NUM_ROOM * NUM_DOCTOR + i * NUM_BMAC + j, 2, _T("无"));
			Clist.SetItemText(NUM_ROOM * NUM_DOCTOR + i * NUM_BMAC + j, 3, _T("无"));
		}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHospitalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHospitalDlg::OnPaint()
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
	int i, j;
	CString st;
	for (i = 0; i < NUM_ROOM; i++)
		for (j = 0; j < NUM_DOCTOR; j++)
		{
			if (head[i][j] <= tail[i][j])
			{
				st = CA2T(c[i][j][head[i][j]].name.c_str());
				if (c[i][j][head[i][j]].start_time[0] == '-')
				{
					CTime tm = CTime::GetCurrentTime();
					CString st = tm.Format("%Y年%m月%d日 %X");
					c[i][j][head[i][j]].start_time = CT2A(st.GetString());
				}
			}
			else
				st = "无";
			Clist.SetItemText(i * NUM_DOCTOR + j, 2, st);
			if (head[i][j] + 1 <= tail[i][j])
				st = CA2T(c[i][j][head[i][j] + 1].name.c_str());
			else
				st = "无";
			Clist.SetItemText(i * NUM_DOCTOR + j, 3, st);
		}
	for (i = 0; i < NUM_BROOM; i++)
		for (j = 0; j < NUM_BMAC; j++)
		{
			if (bhead[i][j] <= btail[i][j])
			{
				st = CA2T(l[i][j][bhead[i][j]].name.c_str());
				if (l[i][j][bhead[i][j]].start_time[0] == '-')
				{
					CTime tm = CTime::GetCurrentTime();
					CString st = tm.Format("%Y年%m月%d日 %X");
					l[i][j][bhead[i][j]].start_time = CT2A(st.GetString());
				}
			}
			else
				st = "无";
			Clist.SetItemText(NUM_ROOM * NUM_DOCTOR + i * NUM_BMAC + j, 2, st);
			if (bhead[i][j] + 1 <= btail[i][j])
				st = CA2T(l[i][j][bhead[i][j] + 1].name.c_str());
			else
				st = "无";
			Clist.SetItemText(NUM_ROOM * NUM_DOCTOR + i * NUM_BMAC + j, 3, st);
		}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHospitalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHospitalDlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CHospitalDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pt(WIDTH, HEIGHT); //定义宽和高
	lpMMI->ptMinTrackSize = pt; //限制最小宽和高
	lpMMI->ptMaxTrackSize = pt; //限制最小宽和高s
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void  CHospitalDlg::in(int room, int doctor, string name, string ID, BOOL bc)
{
	CTime tm = CTime::GetCurrentTime();
	CString st = tm.Format("%Y年%m月%d日 %X");
	if (room >= 0)
	{
		if (tail[room][doctor] + 1 >= NUM_MAX)
			return;
		tail[room][doctor]++;
		c[room][doctor][tail[room][doctor]].name = name;
		c[room][doctor][tail[room][doctor]].ID = ID;
		c[room][doctor][tail[room][doctor]].bc = bc;
		c[room][doctor][tail[room][doctor]].guahao_time = CT2A(st.GetString());
	}
	else
	{
		room = 0 - room - 1;
		if (btail[room][doctor] + 1 >= NUM_MAX)
		{
			Error dlg(_T("所有B超室均已无法容纳."));
			dlg.DoModal();
			return;
		}
		btail[room][doctor]++;
		l[room][doctor][btail[room][doctor]].name = name;
		l[room][doctor][btail[room][doctor]].ID = ID;
		l[room][doctor][btail[room][doctor]].guahao_time = CT2A(st.GetString());
	}
	Invalidate(false);
}

void CHospitalDlg::out(int room, int doctor)
{
	int i, j, ti, tj, m = NUM_MAX;
	CTime tm = CTime::GetCurrentTime();
	CString st = tm.Format("%Y年%m月%d日 %X");
	if (room >= 0)
	{
		if (head[room][doctor] > tail[room][doctor])
			return;
		c[room][doctor][head[room][doctor]].end_time = CT2A(st.GetString());
		head[room][doctor]++;
		if (c[room][doctor][head[room][doctor] - 1].bc)
		{
			for (i = 0; i < NUM_BROOM; i++)
				for (j = 0; j < NUM_BMAC; j++)
					if (btail[i][j] - bhead[i][j] < m)
					{
						ti = i;
						tj = j;
						m = btail[i][j] - bhead[i][j];
					}
			in(0 - ti - 1, tj, c[room][doctor][head[room][doctor] - 1].name, c[room][doctor][head[room][doctor] - 1].ID, c[room][doctor][head[room][doctor] - 1].bc);
		}
	}
	else
	{
		room = 0 - room - 1;
		if (bhead[room][doctor] > btail[room][doctor])
			return;
		l[room][doctor][bhead[room][doctor]].end_time = CT2A(st.GetString());
		bhead[room][doctor]++;
	}
	Invalidate(false);
}

void CHospitalDlg::OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	Clist.ScreenToClient(&point);
	CString st;
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = Clist.SubItemHitTest(&lvinfo);
	int room, doctor;
	if (nItem != -1)
	{
		
		if (lvinfo.iSubItem == 3)
		{
			room = lvinfo.iItem / NUM_DOCTOR;
			doctor = lvinfo.iItem % NUM_DOCTOR;
			if (room >= NUM_ROOM)
			{
				room = room - NUM_ROOM;
				st.Format(_T("%d号机位"), doctor + 1);
				st = CA2T(::broom[room].c_str()) + st + _T("排队状况");
				room = 0 - room - 1;
			}
			else
			{
				st.Format(_T("%d诊间"), doctor + 1);
				st = CA2T(::room[room].c_str()) + st + _T("排队状况");
			}
			Record dlg(room, doctor, this, st);
			dlg.DoModal();
		}
	}
	*pResult = 0;
}

void  CHospitalDlg::GUA(UINT nID)
{
	CString s1, s2;
	int room = (nID - ID_32786) / NUM_DOCTOR, doctor = (nID - ID_32786) % NUM_DOCTOR;
	s1.Format(_T("%d诊间"), doctor + 1);
	s1 = CA2T(::room[room].c_str()) + s1;
	s1 = _T("科室/诊间 : ") + s1;
	s2 = CA2T(::doctor[room * NUM_DOCTOR + doctor].c_str());
	s2 = _T("当值医生 : ") + s2;
	Information dlg(s1, s2);
	if (dlg.DoModal() != IDOK)
		return;
	string data2 = CT2A(dlg.data2.GetString());
	string data1 = CT2A(dlg.data1.GetString());
	in(room, doctor, data2, data1, dlg.c);
}

void  CHospitalDlg::DOE(UINT nID)
{
	int room = (nID - ID_32831) / NUM_DOCTOR, doctor = (nID - ID_32831) % NUM_DOCTOR;
	out(room, doctor);
}

void  CHospitalDlg::DOD(UINT nID)
{
	int room = (nID - ID_32876) / NUM_BMAC, doctor = (nID - ID_32876) % NUM_BMAC;
	room = 0 - room - 1;
	out(room, doctor);
}

void CHospitalDlg::QUE(UINT nID)
{
	CString st;
	int room = (nID - ID_32879) / NUM_DOCTOR, doctor = (nID - ID_32879) % NUM_DOCTOR;
	st.Format(_T("%d诊间"), doctor + 1);
	st = CA2T(::room[room].c_str()) + st + _T("就诊记录，医生 : ");
	st = st + CA2T(::doctor[nID - ID_32879].c_str());
	Diary dlg(room, doctor, this, st);
	dlg.DoModal();
}

void CHospitalDlg::BUE(UINT nID)
{
	CString st;
	int room = (nID - ID_32924) / NUM_BMAC, doctor = (nID - ID_32924) % NUM_BMAC;
	st.Format(_T("%d号机位"), doctor + 1);
	st = CA2T(::broom[room].c_str()) + st + _T("就诊记录");
	room = 0 - room - 1;
	Diary dlg(room, doctor, this, st);
	dlg.DoModal();
}


void CHospitalDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime t;
	t = CTime::GetCurrentTime();
	bar.SetPaneText(0, t.Format("当前时间 : %Y年%m月%d日 %X"));
	CDialog::OnTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}

void CHospitalDlg::NDOE(CCmdUI* pCmdUI)
{
	int room = (pCmdUI->m_nID - ID_32831) / NUM_DOCTOR, doctor = (pCmdUI->m_nID - ID_32831) % NUM_DOCTOR;
	pCmdUI->Enable(head[room][doctor] <= tail[room][doctor]);
}

void CHospitalDlg::NDOD(CCmdUI* pCmdUI)
{
	int room = (pCmdUI->m_nID - ID_32876) / NUM_BMAC, doctor = (pCmdUI->m_nID - ID_32876) % NUM_BMAC;
	pCmdUI->Enable(bhead[room][doctor] <= btail[room][doctor]);
}

void CHospitalDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	ASSERT(pPopupMenu != NULL);
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue;
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;
			}
			state.DoUpdate(this, TRUE);
		}
		else
		{
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}


void CHospitalDlg::GET(UINT ID)
{
	// TODO: 在此添加命令处理程序代码
	ifstream fin;
	fin.open(FILENAME);
	if (fin.is_open() == 0)
	{
		CString st = _T(FILENAME);
		st = _T("找不到文件") + st;
		Error dlg(st);
		dlg.DoModal();
		fin.close();
		return;
	}
	bar.SetPaneText(0, _T("文件读取中..."));
	while (1)
	{
		string d, id, name, bc;
		int i, j, t1, t2, f = -1;
		fin >> d;
		if (fin.eof())
			break;
		for (i = 0; i < NUM_ROOM; i++)
			for (j = 0; j < NUM_DOCTOR; j++)
				if (doctor[i * NUM_DOCTOR + j] == d)
				{
					t1 = i;
					t2 = j;
					f = 1;
					break;
				}
		if (f == -1)
		{
			CString st = CA2T(d.c_str());
			st = _T("不存在医生 : ") + st;
			Error dlg(st);
			dlg.DoModal();
			break;
		}
		fin >> id;
		if (check(id) == -1)
		{
			CString st = CA2T(id.c_str());
			st = _T("不合法ID(非8位数字) : ") + st;
			Error dlg(st);
			dlg.DoModal();
			break;
		}
		fin >> name;
		fin >> bc;
		if ((bc != "N") && (bc != "Y"))
		{
			CString st = CA2T(bc.c_str());
			st = _T("不合法B超选项(仅为Y/N) : ") + st;
			Error dlg(st);
			dlg.DoModal();
			break;
		}
		if (ID == ID_32784)
			Sleep(1000);
		in(t1, t2, name, id, true);
	}
	fin.close();
}
