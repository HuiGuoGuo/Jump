
// JUMPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JUMP.h"
#include "JUMPDlg.h"
#include "afxdialogex.h"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJUMPDlg 对话框



CJUMPDlg::CJUMPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJUMPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	cList = new CList<CPoint, CPoint>();
	ExecuteCmd(_T("adb -P 8888 start-server"));
}

void CJUMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_jump_contrl);
}

BEGIN_MESSAGE_MAP(CJUMPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, &CJUMPDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CJUMPDlg 消息处理程序

BOOL CJUMPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	this->LoadImage();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJUMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJUMPDlg::OnPaint()
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
HCURSOR CJUMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJUMPDlg::ChangeImage(CImage *pImage, CImage *ResultImage, int height, int width)
{
	if (pImage->IsDIBSection())
	{
		CDC* pDC = CDC::FromHandle(pImage->GetDC());
		CBitmap* cBitmap = pDC->GetCurrentBitmap();
		BITMAP bitmap;
		cBitmap->GetBitmap(&bitmap);
		//建立新的CImage
		ResultImage->Create(width, height, bitmap.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());
		ResultImageDC->SetStretchBltMode(HALFTONE);//使用高品质方式
		::SetBrushOrgEx(ResultImageDC->m_hDC, 0, 0, NULL);//调整画刷起点
		StretchBlt(*ResultImageDC, 0, 0, width, height, *pDC, 0,0, pImage->GetWidth(), pImage->GetHeight(),SRCCOPY);
		pImage->Draw(*ResultImageDC, 0, 0, width, height, 0, 0, pImage->GetWidth(), pImage->GetHeight());
		pImage->ReleaseDC();
		ResultImage->ReleaseDC();
	}

}






void CJUMPDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	cList->AddTail(point);
	int size = cList->GetSize();
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	//开始执行跳一跳
	if (size == 2){
		Jump(cList->GetHead(), cList->GetTail());
		cList->RemoveAll();
	//	this->LoadImage();
	}
	
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CJUMPDlg::Jump(CPoint start, CPoint end)
{
	double x  = (end.x - start.x) * 4;
	double y = (end.y - start.y) * 4;

	double instance = pow(pow(x, 2) + pow(y, 2), 0.5);

	CString command;
   // command = _T("adb shell input swipe 320 410 320 410 %d");
	int inst = int(instance * 1.35);
	
	RandCommand(command,inst);
	
	ShellExecute(m_hWnd, NULL, _T("cmd"), command,NULL,SW_HIDE);
	//ExecuteCmd(command);

	this->LoadImage();

}

void CJUMPDlg::LoadImage()
{
	Sleep(2500);
	ExecuteCmd(_T("adb shell screencap -p /sdcard/test/screenshot.png"));
	ExecuteCmd(_T("adb pull /sdcard/test/screenshot.png screenshot.png"));
	CImage img, imDest;
	img.Load(_T("screenshot.png"));

	ChangeImage(&img, &imDest, 480, 270); //1920 * 1080 缩小 4 倍


	HBITMAP hbitmap = imDest.Detach();

	//像操作 BMP 图片一样处理图片 ,下面是显示图片的操作
	CBitmap cBitmap;

	BITMAP bitmap;

	cBitmap.Attach(hbitmap);

	cBitmap.GetBitmap(&bitmap);

	m_jump_contrl.SetBitmap(cBitmap);



}

CJUMPDlg::~CJUMPDlg()
{
	delete cList;
	m_jump_contrl.OnFinalRelease();
	ShellExecute(m_hWnd, _T("open"), _T("cmd"), _T("/C adb kill-server"), NULL, SW_HIDE);
	
}





void CJUMPDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	ShellExecute(m_hWnd, _T("open"), _T("cmd"), _T("/C adb pull /sdcard/test/screenshot.png d:/screenshot.png"), NULL, SW_HIDE);
}

CString CJUMPDlg::ExecuteCmd(CString str)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		MessageBox(_T("Error on CreatePipe()!"));
		return NULL;
	}
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	TCHAR* cmdline = StringToChar(str);
	if (!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		MessageBox(_T("Error on CreateProcess()!"));
		return NULL;
	}
	CloseHandle(hWrite);

	char buffer[4096];
	memset(buffer, 0, 4096);
	CString output;
	DWORD byteRead;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &byteRead, NULL) == NULL)
		{
			break;
		}
		output += buffer;
	}
	return output;
}
TCHAR* CJUMPDlg::StringToChar(CString& str)
{
	int len = str.GetLength();
	TCHAR* tr = str.GetBuffer(len);
	str.ReleaseBuffer();
	return tr;
}

void CJUMPDlg::RandCommand(CString &command, int inst)
{
	for (int i = 0; i < 5; i++){
		i = rand();
		switch (i)
		{
		case 1:
			command.Format(_T("/C adb shell input swipe 321 415 320 410 %d"), inst);
			break;
		case 2:
			command.Format(_T("/C adb shell input swipe 324 410 320 410 %d"), inst);
			break;
		case 3:
			command.Format(_T("/C adb shell input swipe 326 417 320 410 %d"), inst);
			break;
		case 4:
			command.Format(_T("/C adb shell input swipe 322 419 320 410 %d"), inst);
			break;
		case 5:
			command.Format(_T("/C adb shell input swipe 325 415 320 410 %d"), inst);
			break;
		default:
			command.Format(_T("/C adb shell input swipe 320 410 320 410 %d"), inst);
			break;

		}

	}
}
