
// MFCApplication1Dlg.cpp: 구현 파일
//


#include <stdlib.h>
#include <vector>
#include <cmath>

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MINRADIUS 30
#define RADIUSRANGE 20
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
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


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_str(_T(""))
	, m_nRadius(0)
	, m_nX1(0)
	, m_nY1(0)
	, m_nX2(0)
	, m_nY2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_str);
	DDX_Text(pDX, IDC_EDIT1, m_nRadius);
	DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nY2);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_LOADCENTER, &CMFCApplication1Dlg::OnBnClickedLoadcenter)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCApplication1Dlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_ACTION, &CMFCApplication1Dlg::OnBnClickedAction)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnBnClickedLoadcenter()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}

	static TCHAR BASED_CODE szFilter[] = _T("");

	CFileDialog dlg(TRUE, _T(".jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);


	CClientDC dc(this);

	if (IDOK == dlg.DoModal())

	{
		CString pathName = dlg.GetPathName();

		if (m_image != NULL)
		{
			m_image.Destroy();
		}
		m_image.Load(pathName);

		CClientDC dc(this);
		m_image.Draw(dc, 0, 40);
	}
	else
	{
		return;
	}

	POINT outLinePoint;
	POINT centerPoint = GetCenterPositionAndOutLine(&dc, outLinePoint);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(outLinePoint);
	dc.LineTo(centerPoint);

	{
		POINT start, end;

		start.x = centerPoint.x - 2;
		start.y = centerPoint.y - 2;

		end.x = centerPoint.x + 2;
		end.y =  centerPoint.y + 2;

		dc.MoveTo(start);
		dc.LineTo(end);
	}

	{
		POINT start, end;

		start.x = centerPoint.x - 2;
		start.y = centerPoint.y + 2;

		end.x = centerPoint.x + 2;
		end.y = centerPoint.y - 2;

		dc.MoveTo(start);
		dc.LineTo(end);
	}

	UpdateData(true);

	CString str = _T("");
	str.Format(_T("%d , %d"), centerPoint.x, centerPoint.y - 40);
	m_str = str;

	int dx = centerPoint.x - outLinePoint.x;
	int dy = centerPoint.y - outLinePoint.y;

	int distance = (int)sqrt(dx * dx + dy * dy);

	m_nRadius = distance;

	UpdateData(false);
}

POINT CMFCApplication1Dlg::GetCenterPositionAndOutLine(CDC* pDC, POINT& outLinePoint)
{
	CRect rect;
	GetWindowRect(&rect);

	int nWidth = rect.Width();
	int nHeight = rect.Height();

	POINT point;
	point.x = 0;
	point.y = 0;

	COLORREF whiteColor(RGB(0, 0, 0));
	COLORREF blackColor(RGB(255, 255, 255));

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, nWidth - 15, nHeight - 38);

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.BitBlt(0, 0, nWidth, nHeight, pDC, 0, 0, SRCCOPY);

	BITMAP bm;
	bitmap.GetObject(sizeof(BITMAP), (LPSTR)&bm);
	BYTE* pData = NULL;
	pData = (BYTE*)malloc(bm.bmWidthBytes * bm.bmHeight);
	memset(pData, 0x00, bm.bmWidthBytes * bm.bmHeight);
	bitmap.GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, pData);
	RGBQUAD* pRgb = (RGBQUAD*)pData;

	for (int y = 0; y < bm.bmHeight; y++)
	{
		for (int x = 0; x < bm.bmWidth; x++)
		{
			int nPos = x + (y * bm.bmWidth);

			BYTE r = pRgb[nPos].rgbRed;
			BYTE g = pRgb[nPos].rgbGreen;
			BYTE b = pRgb[nPos].rgbBlue;

			auto color = RGB(r, g, b);

			if ((whiteColor == color) || (blackColor == color))
			{
				point.x = x;
				point.y = y;
				break;
			}
		}
	}

	free(pData);
	pData = NULL;

	POINT lx = GetOutlinePointX(pDC, point, false);
	POINT rx = GetOutlinePointX(pDC, point, true);

	int centerX = (lx.x + rx.x) / 2;

	POINT centerXPoint;
	point.x = centerX;
	point.y = lx.y;


	POINT uy = GetOutlinePointY(pDC, point, false);
	POINT dy = GetOutlinePointY(pDC, point, true);

	POINT centerPoint;
	centerPoint.x = centerX;
	centerPoint.y = ((uy.y + dy.y) / 2);

	outLinePoint = lx;
	return centerPoint;

}

POINT CMFCApplication1Dlg::GetOutlinePointX(CDC* pDC, POINT point, bool bDirection)
{
	if (point.x == 0 && point.y == 0)
	{
		return point;
	}

	int direction;
	if (bDirection)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}

	int dx = (MINRADIUS + RADIUSRANGE) * direction;

	COLORREF whiteColor(RGB(0, 0, 0));

	bool bInCircle = true;
	while (bInCircle)
	{
		auto color = pDC->GetPixel(point);

		if (color != whiteColor)
		{
			bInCircle = false;
			continue;
		}

		point.x += dx;
	}

	while (!bInCircle)
	{
		auto color = pDC->GetPixel(point);

		if (color == whiteColor)
		{
			bInCircle = true;
			continue;
		}

		point.x += (direction * -1);
	}

	return point;
}

POINT CMFCApplication1Dlg::GetOutlinePointY(CDC* pDC, POINT point, bool bDirection)
{
	if (point.x == 0 && point.y == 0)
	{
		return point;
	}

	int direction;
	if (bDirection)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}

	int dy = (MINRADIUS + RADIUSRANGE) * direction;

	COLORREF whiteColor(RGB(0, 0, 0));

	bool bInCircle = true;
	while (bInCircle)
	{
		auto color = pDC->GetPixel(point);

		if (color != whiteColor)
		{
			bInCircle = false;
			continue;
		}

		point.y += dy;
	}

	while (!bInCircle)
	{
		auto color = pDC->GetPixel(point);

		if (color == whiteColor)
		{
			bInCircle = true;
			continue;
		}

		point.y += (direction * -1);
	}

	return point;
}

void CMFCApplication1Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	lpMMI->ptMinTrackSize = CPoint(800, 600);
	lpMMI->ptMaxTrackSize = CPoint(800, 600);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CMFCApplication1Dlg::OnBnClickedBtnDraw()
{
	CRect rect;
	GetWindowRect(&rect);

	int nZeroX = 0;
	int nZeroY = 40;

	int nWidth = rect.Width() - 16;
	int nHeight = rect.Height() - 39;

	UpdateData(true);
	CClientDC dc(this);
	srand((unsigned int)time(NULL));

	srand((unsigned)time(NULL));
	int radius = (rand() % RADIUSRANGE) + MINRADIUS;
	m_nRandRadius = radius;

	int rx = m_nX1 + nZeroX;
	int ry = m_nY1 + nZeroY;

	if (rx - radius <= nZeroX)
	{
		rx = radius;
	}
	else if(rx + radius >= nWidth)
	{
		rx = nWidth - radius;
	}
	
	if (ry - radius <= nZeroY)
	{
		ry = radius + nZeroY;
	}
	else if (ry + radius >= nHeight)
	{
		ry = nHeight - radius;
	}

	m_nX1 = rx - nZeroX;
	m_nY1 = ry - nZeroY;

	dc.FillSolidRect(nZeroX, nZeroY, nWidth, nHeight, RGB(128, 128, 128));
	DrawCircle(&dc, rx, ry, radius);

	UpdateData(false);
}

void CMFCApplication1Dlg::DrawCircle(CDC* pDC, int x, int y, int radius)
{
	radius /= 2;
	pDC->Ellipse(x-radius, y-radius, x + radius, y + radius);
}

void CMFCApplication1Dlg::OnBnClickedAction()
{
	OnBnClickedBtnDraw();

	CClientDC dc(this);
	CRect rect;
	GetWindowRect(&rect);

	int nZeroX = 0;
	int nZeroY = 40;
	int nWidth = rect.Width() - 16;
	int nHeight = rect.Height() - 39;

	int radius = m_nRandRadius;
	{
		UpdateData(true);
		int rx = m_nX2 + nZeroX;
		int ry = m_nY2 + nZeroY;

		if (rx - radius <= nZeroX)
		{
			rx = radius;
		}
		else if (rx + radius >= nWidth)
		{
			rx = nWidth - radius;
		}

		if (ry - radius <= nZeroY)
		{
			ry = radius + nZeroY;
		}
		else if (ry + radius >= nHeight)
		{
			ry = nHeight - radius;
		}

		m_nX2 = rx - nZeroX;
		m_nY2 = ry - nZeroY;
		UpdateData(false);
	}

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.BitBlt(0, 0, nWidth, nHeight, &dc, 0, 0, SRCCOPY);

	int dx = (int)((m_nX2 - m_nX1) / (double)10);
	int dy = (int)((m_nY2 - m_nY1) / (double)10);

	int rx = m_nX1 + nZeroX;
	int ry = m_nY1 + nZeroY;

	for (int i = 0; i < 11; ++i)
	{
		UpdateData(true);

		if (i == 10)
		{
			rx = m_nX2 + nZeroX;
			ry = m_nY2 + nZeroY;
		}

		dc.FillSolidRect(nZeroX, nZeroY, nWidth, nHeight, RGB(128, 128, 128));
		DrawCircle(&dc, rx, ry, radius);

		rx += dx;
		ry += dy;

		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);

		CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

		memDC.BitBlt(0, 0, nWidth, nHeight, &dc, 0, 40, SRCCOPY);

		TCHAR path[MAX_PATH] = { 0, };
		GetCurrentDirectory(MAX_PATH, path);

		CString filename = _T("");
		filename.Format(_T("\\save%d.bmp"), i);
		CString strPath = CString(path) + filename.GetString();

		CImage image;
		image.Attach(bitmap);
		image.Save(strPath);

		Sleep(100);

		UpdateData(false);
	}

}
