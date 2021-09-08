#pragma once


// Record 对话框
#include "HospitalDlg.h"

class Record : public CDialogEx
{
	DECLARE_DYNAMIC(Record)

public:
	Record(int r, int d, CHospitalDlg* DLG, CString st, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Record();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic title;
	CString content, total;
	CListCtrl clist;
	int room, doctor, sel;
	CHospitalDlg* dlg;
	virtual BOOL OnInitDialog();
	CStatic count;
};
