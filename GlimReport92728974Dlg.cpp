
// GlimReport92728974Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GlimReport92728974.h"
#include "GlimReport92728974Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CGlimReport92728974Dlg dialog

bool IsInCircle(int i, int j, int cx, int  cy, int rad)
{
	auto dx = (double)i - cx;
	auto dy = (double)j - cy;
	auto dr = dx * dx + dy * dy;
	return dr < (double)rad* rad;
}

CGlimReport92728974Dlg::CGlimReport92728974Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMREPORT92728974_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimReport92728974Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_radius, _radius);
	DDV_MinMaxInt(pDX, _radius, 2, 1000);
}

BEGIN_MESSAGE_MAP(CGlimReport92728974Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MakeCircle, &CGlimReport92728974Dlg::OnBnClickedMakecircle)
END_MESSAGE_MAP()


// CGlimReport92728974Dlg message handlers
void CGlimReport92728974Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pDlgImage)		
		delete m_pDlgImage;
}
BOOL CGlimReport92728974Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MoveWindow(0, 0, 640, 480 + 100);// 1280, 800);
	m_pDlgImage = new CImageDlg;
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);

	UpdateData(0);
	CenterWindow();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGlimReport92728974Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGlimReport92728974Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGlimReport92728974Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGlimReport92728974Dlg::OnBnClickedMakecircle()
{
	UpdateData();
	CRect crc;
	m_pDlgImage->GetClientRect(crc);
	int w = crc.Width();
	int h = crc.Height();

	int cx = (rand() % (w - (2*_radius))) + _radius; // 반지름 만큼 작은 사각형
	int cy = (rand() % (h - (2*_radius))) + _radius;

	MakeCircle(cx, cy, _radius);
	CRect rc(CPoint(cx - _radius, cy - _radius), CSize(2*_radius, 2*_radius));

	// 추가로 그릴것이 있으면 여기에 넣어준다.
	m_pDlgImage->_fnPaint = [this, rc, cx, cy](CDC& dc) {
		{
			CPen  pen;	pen.CreatePen(PS_SOLID, 1, COLOR_YELLOW);
			CBrush brs;	brs.CreateStockObject(NULL_BRUSH);
			CBrush* pOldBr  = dc.SelectObject(&brs);
			CPen*   pOldPen = dc.SelectObject(&pen);
			KAtEnd defer = [&]() {//GID 객체 마무리 할거 여기 미리 예약 한다.
				dc.SelectObject(pOldPen);
				dc.SelectObject(pOldBr);
				pen.DeleteObject();
				brs.DeleteObject();
			};

			dc.Ellipse(rc);
		}

		CPoint hp = _cog;// +rc.Size();// 무게 중심
		{
			CPen pen2;
			pen2.CreatePen(PS_SOLID, 1, COLOR_RED);
			CPen* pOldPen2 = dc.SelectObject(&pen2);
			int ln = (int)(_radius * 0.25);
			KAtEnd defer = [&]() {
				dc.SelectObject(pOldPen2);
				pen2.DeleteObject();
			};

			dc.MoveTo(hp.x - ln, hp.y);
			dc.LineTo(hp.x + ln, hp.y);
			dc.MoveTo(hp.x, hp.y - ln);
			dc.LineTo(hp.x, hp.y + ln);
		}
	};
	m_pDlgImage->Invalidate(FALSE);
}

void CGlimReport92728974Dlg::MakeCircle(int cx, int cy, int rad)
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, (size_t)nWidth * nHeight);

	auto size = nPitch * nHeight;

	int nTh = 0x80;

	CRect rect(CPoint(cx-rad, cy-rad), CSize(rad*2, rad*2));// 큰그림 가운데 이 영역에 픽샐값을 파렛트 한바이트 값을 랜덤으로 넣으면 그레이 점이 박히겠지.
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for(int j = rect.top; j < rect.bottom; j++) {
		for(int i = rect.left; i < rect.right; i++) {
			auto r = rand();
			auto tv = r % 0xff;
			if(IsInCircle(i,j,cx,cy,rad))
			{
				fm[j * nPitch + i] = tv;// rand() % 0xff;
				//TRACE("(%5d, %5d) %12d, %3d\n", i, j, r, tv);
				if(tv > nTh) {// 픽셀값 바이트가 0x80보다 크면 하나씩 증가 하면 무게 중심이 되나?
					nSumX += i;
					nSumY += j;
					nCount++;
				}
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;//무게 중심이 되나?
	_cog = CPoint((int)dCenterX, (int)dCenterY);
}


