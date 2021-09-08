// Diary.cpp: 实现文件
//

#include "pch.h"
#include "Hospital.h"
#include "Diary.h"
#include "afxdialogex.h"


// Diary 对话框
#define EW 23

IMPLEMENT_DYNAMIC(Diary, CDialogEx)

Diary::Diary(int r, int d, CHospitalDlg* DLG, CString st, CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_DIALOG4, pParent)
{
	room = r;
	doctor = d;
	dlg = DLG;
	content = st;
	if (room>=0)
		total.Format(_T("共%d条记录."), dlg->tail[room][doctor] + 1);
	else
		total.Format(_T("共%d条记录."), dlg->btail[room][doctor] + 1);

}

Diary::~Diary()
{
}

void Diary::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE, title);
	DDX_Control(pDX, IDC_LIST1, clist);
	title.SetWindowText(content);
	DDX_Control(pDX, IDC_COUNT2, count);
	count.SetWindowText(total);
}


BEGIN_MESSAGE_MAP(Diary, CDialogEx)
END_MESSAGE_MAP()


// Diary 消息处理程序


BOOL Diary::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	CString st;
	int w, i;
	// 获取编程语言列表视图控件的位置和大小   
	clist.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	clist.SetExtendedStyle(clist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	w = int(rect.Width()) - EW;
	clist.InsertColumn(0, _T("ID"), LVCFMT_CENTER, w - w / 6 - w / 8 - 3 * w / 5, 0);
	clist.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, w / 6, 1);
	clist.InsertColumn(2, _T("状态"), LVCFMT_CENTER, w / 8, 2);
	if (room >= 0)
	{
		clist.InsertColumn(3, _T("挂号时间"), LVCFMT_CENTER, w / 5, 3);
		clist.InsertColumn(4, _T("开始时间"), LVCFMT_CENTER, w / 5, 4);
		clist.InsertColumn(5, _T("结束时间"), LVCFMT_CENTER, w / 5, 5);
		for (i = 0; i <= dlg->tail[room][doctor]; i++)
		{
			clist.InsertItem(i, CA2T(dlg->c[room][doctor][i].ID.c_str()));
			clist.SetItemText(i, 1, CA2T(dlg->c[room][doctor][i].name.c_str()));
			if (i < dlg->head[room][doctor])
				st = "已就诊";
			else
				if (i > dlg->head[room][doctor])
					st = "等待就诊";
				else
					st = "就诊中";
			clist.SetItemText(i, 2, st);
			clist.SetItemText(i, 3, dlg->c[room][doctor][i].guahao_time);
			clist.SetItemText(i, 4, dlg->c[room][doctor][i].start_time);
			clist.SetItemText(i, 5, dlg->c[room][doctor][i].end_time);
		}
	}
	else
	{
		clist.InsertColumn(3, _T("准备时间"), LVCFMT_CENTER, w / 5, 3);
		clist.InsertColumn(4, _T("开始时间"), LVCFMT_CENTER, w / 5, 4);
		clist.InsertColumn(5, _T("结束时间"), LVCFMT_CENTER, w / 5, 5);
		room = 0 - room - 1;
		for (i = 0; i <= dlg->btail[room][doctor]; i++)
		{
			clist.InsertItem(i, CA2T(dlg->l[room][doctor][i].ID.c_str()));
			clist.SetItemText(i, 1, CA2T(dlg->l[room][doctor][i].name.c_str()));
			if (i < dlg->bhead[room][doctor])
				st = "已就诊";
			else
				if (i > dlg->bhead[room][doctor])
					st = "等待就诊";
				else
					st = "就诊中";
			clist.SetItemText(i, 2, st);
			clist.SetItemText(i, 3, dlg->l[room][doctor][i].guahao_time);
			clist.SetItemText(i, 4, dlg->l[room][doctor][i].start_time);
			clist.SetItemText(i, 5, dlg->l[room][doctor][i].end_time);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
