#pragma once


// Information 对话框

class Information : public CDialogEx
{
	DECLARE_DYNAMIC(Information)

public:
	Information(CString s1, CString s2, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Information();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif
	CString content1, content2, data1, data2;
	BOOL c;
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CStatic message1;
	CStatic message2;
	CButton BC;
};
