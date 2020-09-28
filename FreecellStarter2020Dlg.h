
// FreecellStarter2020Dlg.h : header file
//

#pragma once
#include "Cell.h"

// CFreecellStarter2020Dlg dialog
class CFreecellStarter2020Dlg : public CDialogEx
{
// Construction
public:
	CFreecellStarter2020Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FREECELLSTARTER2020_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Cell* mCells[16];
	int mFirstClick = 0;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFileQuit();
	afx_msg void OnFileRestart();
	// DoubleBufferDrawing();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void MyDrawing(CDC& pDC);
	afx_msg void DoubleBufferDrawing(CDC& dc);
	afx_msg void OnInitMenu(CMenu* pMenu);
};
