// Information.cpp: 实现文件
//

#include "pch.h"
#include "Hospital.h"
#include "HospitalDlg.h"
#include "Information.h"
#include "afxdialogex.h"
#include "Error.h"
#include <string>
using namespace std;
// Information 对话框

IMPLEMENT_DYNAMIC(Information, CDialogEx)

Information::Information(CString s1, CString s2, CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_DIALOG3, pParent)
{
	content1 = s1;
	content2 = s2;
}

Information::~Information()
{
}

void Information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_S1, message1);
	DDX_Control(pDX, IDC_S2, message2);
	message1.SetWindowText(content1);
	message2.SetWindowText(content2);
	DDX_Control(pDX, IDC_CHECK1, BC);
}


BEGIN_MESSAGE_MAP(Information, CDialogEx)
	ON_BN_CLICKED(IDOK, &Information::OnBnClickedOk)
END_MESSAGE_MAP()

// Information 消息处理程序
void Information::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(data1);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(data2);
	int s = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	if (s == 1)
		c = true;
	else
		c = false;
	string st = CT2A(data1.GetString());
	if (st.size() == 0)
		return;
	if (check(st) == -1)
	{
		Error dlg(_T("ID由8位数字组成."));
		dlg.DoModal();
		return;
	}
	Invalidate();
	CDialogEx::OnOK();
}