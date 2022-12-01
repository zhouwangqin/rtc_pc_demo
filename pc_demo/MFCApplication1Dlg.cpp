
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "ZXSdk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void local_video_func(const char* uid, int video_type,
	const unsigned char* data_y, const unsigned char* data_u, const unsigned char* data_v,
	int stride_y, int stride_u, int stride_v, unsigned int width, unsigned int height)
{
	OutputDebugStringA("------local_video_func------\r\n");
}

void remote_video_func(const char* uid, int video_type,
	const unsigned char* data_y, const unsigned char* data_u, const unsigned char* data_v,
	int stride_y, int stride_u, int stride_v, unsigned int width, unsigned int height)
{
	OutputDebugStringA("------remote_video_func------\r\n");
}

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

// CMFCApplication1Dlg 对话框

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_START, &CMFCApplication1Dlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CMFCApplication1Dlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_JOIN, &CMFCApplication1Dlg::OnBnClickedBtnJoin)
	ON_BN_CLICKED(IDC_BTN_LEAVE, &CMFCApplication1Dlg::OnBnClickedBtnLeave)
	ON_BN_CLICKED(IDC_BTN_SC_START, &CMFCApplication1Dlg::OnBnClickedBtnScStart)
	ON_BN_CLICKED(IDC_BTN_SC_STOP, &CMFCApplication1Dlg::OnBnClickedBtnScStop)
	ON_BN_CLICKED(IDC_BTN_PUB_START, &CMFCApplication1Dlg::OnBnClickedBtnPubStart)
	ON_BN_CLICKED(IDC_BTN_PUB_STOP, &CMFCApplication1Dlg::OnBnClickedBtnPubStop)
	ON_BN_CLICKED(IDC_BTN_MUTE, &CMFCApplication1Dlg::OnBnClickedBtnMute)
	ON_BN_CLICKED(IDC_BTN_UNMUTE, &CMFCApplication1Dlg::OnBnClickedBtnUnmute)
END_MESSAGE_MAP()

// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	leaveRoom();
	freeSdk();
}

void CMFCApplication1Dlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	setServerIp("81.69.253.187", 8443);
	//setServerIp("1.116.231.35", 8443);
	setFrameRate(6);
	setLocalVideo(local_video_func);
	setRemoteVideo(remote_video_func);
	initSdk("1234");
}

void CMFCApplication1Dlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	freeSdk();
}

void CMFCApplication1Dlg::OnBnClickedBtnJoin()
{
	// TODO: 在此添加控件通知处理程序代码
	joinRoom("100");
}

void CMFCApplication1Dlg::OnBnClickedBtnLeave()
{
	// TODO: 在此添加控件通知处理程序代码
	leaveRoom();
}

void CMFCApplication1Dlg::OnBnClickedBtnScStart()
{
	// TODO: 在此添加控件通知处理程序代码
	setScreen(true);
}

void CMFCApplication1Dlg::OnBnClickedBtnScStop()
{
	// TODO: 在此添加控件通知处理程序代码
	setScreen(false);
}

void CMFCApplication1Dlg::OnBnClickedBtnPubStart()
{
	// TODO: 在此添加控件通知处理程序代码
	setPublish(true);
}

void CMFCApplication1Dlg::OnBnClickedBtnPubStop()
{
	// TODO: 在此添加控件通知处理程序代码
	setPublish(false);
}

void CMFCApplication1Dlg::OnBnClickedBtnMute()
{
	// TODO: 在此添加控件通知处理程序代码
	//setMicrophoneMute(true);
}

void CMFCApplication1Dlg::OnBnClickedBtnUnmute()
{
	// TODO: 在此添加控件通知处理程序代码
	//setMicrophoneMute(false);
}
