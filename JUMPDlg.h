
// JUMPDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CJUMPDlg �Ի���
class CJUMPDlg : public CDialogEx
{
// ����
public:
	CJUMPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JUMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
