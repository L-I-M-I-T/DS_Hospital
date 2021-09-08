#pragma once

// Error 对话框

class Error : public CDialogEx
{
	DECLARE_DYNAMIC(Error)

public:
	Error(CString st, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Error();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic message;
	CString content;
};
