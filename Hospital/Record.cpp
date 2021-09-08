// Record.cpp: 实现文件
//

#include "pch.h"
#include "Hospital.h"
#include "Record.h"
#include "afxdialogex.h"

// Record 对话框
#define EW 23

IMPLEMENT_DYNAMIC(Record, CDialogEx)

Record::Record(int r, int d, CHospitalDlg* DLG, CString st, CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_DIALOG1, pParent)
{
	room = r;
	doctor = d;
    dlg = DLG;
	content = st;
	if (room >= 0)
		total.Format(_T("共%d人排队中."), (dlg->tail[room][doctor] - dlg->head[room][doctor] < 0) ? 0 : (dlg->tail[room][doctor] - dlg->head[room][doctor]));
	else
		total.Format(_T("共%d人排队中."), (dlg->btail[room][doctor] - dlg->bhead[room][doctor] < 0) ? 0 : (dlg->btail[room][doctor] - dlg->bhead[room][doctor]));
}

Record::~Record()
{
}

void Record::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE, title);
	DDX_Control(pDX, IDC_LIST1, clist);
	title.SetWindowText(content);
	DDX_Control(pDX, IDC_COUNT1, count);
	count.SetWindowText(total);
}


BEGIN_MESSAGE_MAP(Record, CDialogEx)
END_MESSAGE_MAP()


// Record 消息处理程序


BOOL Record::OnInitDialog()
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
	clist.InsertColumn(0, _T("ID"), LVCFMT_CENTER, w / 6, 0);
	clist.InsertColumn(1, _T("号序"), LVCFMT_CENTER, w / 6, 1);
	clist.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, w / 6, 2);
	if (room >= 0)
	{
		clist.InsertColumn(3, _T("挂号时间"), LVCFMT_CENTER, w - w / 6 * 3, 3);
		for (i = dlg->head[room][doctor] + 1; i <= dlg->tail[room][doctor]; i++)
		{
			clist.InsertItem(i - dlg->head[room][doctor] - 1, CA2T(dlg->c[room][doctor][i].ID.c_str()));
			clist.SetItemText(i - dlg->head[room][doctor] - 1, 1, CA2T(std::to_string(i + 1).c_str()));
			clist.SetItemText(i - dlg->head[room][doctor] - 1, 2, CA2T(dlg->c[room][doctor][i].name.c_str()));
			clist.SetItemText(i - dlg->head[room][doctor] - 1, 3, dlg->c[room][doctor][i].guahao_time);
		}
	}
	else
	{
		clist.InsertColumn(3, _T("准备时间"), LVCFMT_CENTER, w - w / 6 * 3, 3);
		room = 0 - room - 1;
		for (i = dlg->bhead[room][doctor] + 1; i <= dlg->btail[room][doctor]; i++)
		{
			clist.InsertItem(i - dlg->bhead[room][doctor] - 1, CA2T(dlg->l[room][doctor][i].ID.c_str()));
			clist.SetItemText(i - dlg->bhead[room][doctor] - 1, 1, CA2T(std::to_string(i + 1).c_str()));
			clist.SetItemText(i - dlg->bhead[room][doctor] - 1, 2, CA2T(dlg->l[room][doctor][i].name.c_str()));
			clist.SetItemText(i - dlg->bhead[room][doctor] - 1, 3, dlg->l[room][doctor][i].guahao_time);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
