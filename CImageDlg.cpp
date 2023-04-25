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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;// color table�� 0 ~ 256 �� �ְ�
		m_image.SetColorTable(0, 256, rgb);// �׷��� 
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, (size_t)nWidth * nHeight);//����������
}

void CImageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
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