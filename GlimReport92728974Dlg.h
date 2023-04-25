
// GlimReport92728974Dlg.h : header file
//

#pragma once
#include "CImageDlg.h"
#include <tuple>
// CGlimReport92728974Dlg dialog
class CGlimReport92728974Dlg : public CDialogEx
{
// Construction
public:
	CGlimReport92728974Dlg(CWnd* pParent = nullptr);	// standard constructor
	CImageDlg* m_pDlgImage {nullptr};

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMREPORT92728974_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CPoint _cog {0,0};//무게중심
// Implementation
protected:
	HICON m_hIcon;
	void MakeCircle(int cx, int cy, int r);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int _radius {50};
	afx_msg void OnBnClickedMakecircle();
};
