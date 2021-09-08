
// HospitalDlg.h: 头文件
//

#pragma once
#include <string>
using namespace std;

#define NUM_ROOM 15
#define NUM_DOCTOR 3
#define NUM_MAX 100
#define NUM_BROOM 1
#define NUM_BMAC 3
const string room[NUM_ROOM] = { 
	"呼吸内科","消化内科","神经内科","心血管内科" ,
	"普通外科" ,"神经外科" ,"肝胆外科" ,"烧伤科" ,
	"骨外科" ,"妇科" ,"儿科综合" ,"肿瘤内科" ,
	"肿瘤外科" ,"皮肤科" ,"口腔科" 
};
const string doctor[NUM_ROOM * NUM_DOCTOR] = {
	"朱然","孙桓","王金虎",
	"安倍","川普","卢武铉",
	"曹奂","张曼成","程远志",
	"句扶","高翔","马元义",
	"扁鹊","左灵","陈公台",
	"简雍","陈震","华佗",
	"魏文昌","陈式","王平",
	"马幼常","山县昌景","于文则",
	"宗一","王少博","陈月华",
	"朱辰","张春华","王异",
	"赵月","管辂","江炳恒",
	"汪乐平","罗哲正","徐德民",
	"Krose","吴梓穆","高进",
	"彭来","刘公嗣","夏侯妙才",
	"唐媛媛","万昌吉","纪灵"
};
const string broom[NUM_BROOM] = { "B超室" };
const string bmac[NUM_BMAC] = { "001机","002机","003机" };

struct client
{
	string name;
	string ID;
	CString guahao_time;
	CString start_time;
	CString end_time;
	BOOL bc;
};

// CHospitalDlg 对话框
class CHospitalDlg : public CDialogEx
{
// 构造
public:
	CHospitalDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITAL_DIALOG };
#endif
	client c[NUM_ROOM][NUM_DOCTOR][NUM_MAX], l[NUM_BROOM][NUM_BMAC][NUM_MAX];
	int  loading, head[NUM_ROOM][NUM_DOCTOR], tail[NUM_ROOM][NUM_DOCTOR], bhead[NUM_BROOM][NUM_BMAC], btail[NUM_BROOM][NUM_BMAC];
	CStatusBar bar;
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
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl Clist;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void in(int room, int doctor, string name, string ID, BOOL bc);
	void out(int room, int doctor);
	afx_msg void OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void GET(UINT nID);
	afx_msg void GUA(UINT nID);
	afx_msg void DOE(UINT nID);
	afx_msg void DOD(UINT nID);
	afx_msg void QUE(UINT nID);
	afx_msg void BUE(UINT nID);
	afx_msg void NDOE(CCmdUI* pCmdUI);
	afx_msg void NDOD(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
};

int check(string st);