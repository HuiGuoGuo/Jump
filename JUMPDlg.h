
// JUMPDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CJUMPDlg 对话框
class CJUMPDlg : public CDialogEx
{
// 构造
public:
	CJUMPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JUMP_DIALOG };

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
	CStatic m_jump_contrl;
	void ChangeImage(CImage *pImage,CImage *ResultImapge,int height,int width);
	afx_msg void OnStnClickedStaticImage();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CList<CPoint, CPoint> *cList;
	void Jump(CPoint start, CPoint end);
	virtual ~CJUMPDlg();
	BOOLEAN flag = TRUE;
	void LoadImage();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	CString CJUMPDlg::ExecuteCmd(CString str);
	TCHAR* CJUMPDlg::StringToChar(CString& str);
	void RandCommand(CString& command,int inst);
};
