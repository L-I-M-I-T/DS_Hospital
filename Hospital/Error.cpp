// Error.cpp: 实现文件
//

#include "pch.h"
#include "Hospital.h"
#include "Error.h"
#include "afxdialogex.h"


// Error 对话框

IMPLEMENT_DYNAMIC(Error, CDialogEx)

Error::Error(CString st,CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_DIALOG2, pParent)
{
	content = st;
}

Error::~Error()
{
}

void Error::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ERR, message);
	message.SetWindowText(content);
}


BEGIN_MESSAGE_MAP(Error, CDialogEx)
END_MESSAGE_MAP()


// Error 消息处理程序
