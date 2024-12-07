
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedLoadcenter();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	afx_msg void OnBnClickedBtnDraw();

	afx_msg void OnBnClickedAction();

	void DrawCircle(CDC* pDC, int x, int y, int radius);
	POINT GetCenterPositionAndOutLine(CDC* pDC, POINT& radius);
	POINT GetOutlinePointX(CDC* pDC, POINT point, bool bDirection);
	POINT GetOutlinePointY(CDC* pDC, POINT point, bool bDirection);

public:
	int m_nRadius;
	int m_nX1;
	int m_nY1;
	int m_nX2;
	int m_nY2;

	int m_nRandRadius;

	CString m_str;

	CImage m_image;
};

