// CImageDlg.cpp : implementation file
//

#include "pch.h"
#include "GlimReport92728974.h"
#include "CImageDlg.h"
#include "afxdialogex.h"


// CImageDlg dialog

IMPLEMENT_DYNAMIC(CImageDlg, CDialogEx)

CImageDlg::CImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
{

}

CImageDlg::~CImageDlg()
{
}

void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CImageDlg message handlers
BOOL CImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Origin Image"));
	MoveWindow(0, 0, 640, 480);
	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CImageDlg::InitImage()
{
	int nWidth = 4096 * 8;
	int nHeight = 4096 * 8;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if(nBpp == 8) {
		static RGBQUAD rgb[256];
		for(int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;// color table에 0 ~ 256 을 넣고
		m_image.SetColorTable(0, 256, rgb);// 그레이 
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, (size_t)nWidth * nHeight);//검은색으로
}

void CImageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if(m_image)
		m_image.Draw(dc, 0, 0);
	
	//std::function<void(CDC*)> _fnPaint;
	if(_fnPaint)
		_fnPaint(dc);
	
	drawData(&dc);
}

void CImageDlg::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);
	CPen* pOldPen = pDC->SelectObject(&pen);
	for(int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(1, 1);
		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);
}