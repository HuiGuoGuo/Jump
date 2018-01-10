
// JUMPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JUMP.h"
#include "JUMPDlg.h"
#include "afxdialogex.h"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CJUMPDlg �Ի���



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


// CJUMPDlg ��Ϣ�������

BOOL CJUMPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	this->LoadImage();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJUMPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		//�����µ�CImage
		ResultImage->Create(width, height, bitmap.bmBitsPixel);
		CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());
		ResultImageDC->SetStretchBltMode(HALFTONE);//ʹ�ø�Ʒ�ʷ�ʽ
		::SetBrushOrgEx(ResultImageDC->m_hDC, 0, 0, NULL);//������ˢ���
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��ʼִ����һ��
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

	ChangeImage(&img, &imDest, 480, 270); //1920 * 1080 ��С 4 ��


	HBITMAP hbitmap = imDest.Detach();

	//����� BMP ͼƬһ������ͼƬ ,��������ʾͼƬ�Ĳ���
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
