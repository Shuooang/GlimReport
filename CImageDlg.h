#pragma once
#include <functional>


// CImageDlg dialog
#define MAX_POINT	1000

class CImageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageDlg)

public:
	CImageDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CImageDlg();
	CWnd* m_pParent;
	CImage m_image;
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMAGE };
#endif
	std::function<void(CDC&)> _fnPaint;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void InitImage();
	void drawData(CDC* pDC);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};
