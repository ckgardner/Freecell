
// FreecellStarter2020Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FreecellStarter2020.h"
#include "FreecellStarter2020Dlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"

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


// CFreecellStarter2020Dlg dialog



CFreecellStarter2020Dlg::CFreecellStarter2020Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FREECELLSTARTER2020_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreecellStarter2020Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreecellStarter2020Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FILE_QUIT, &CFreecellStarter2020Dlg::OnFileQuit)
	ON_COMMAND(ID_FILE_RESTART, &CFreecellStarter2020Dlg::OnFileRestart)
	ON_WM_ERASEBKGND()
	ON_WM_INITMENU()
END_MESSAGE_MAP()


// CFreecellStarter2020Dlg message handlers

BOOL CFreecellStarter2020Dlg::OnInitDialog()
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
	bool ok = InitializeCards();
	if (!ok)
	{
		int result = MessageBox(L"Error loading cards.dll", L"Bad", MB_OK);
		return FALSE; // FIX later. This doesn't end the program!
	}

	// Make the cells:
	const int SCREEN_MARGIN = 10;
	int left = SCREEN_MARGIN;
	int top = SCREEN_MARGIN;
	int cellWidth = gCardWidth + 2 * CELL_MARGIN;
	int cellHeight = gCardHeight + 2 * CELL_MARGIN;
	for (int i = 0; i < 4; i++)
	{
		mCells[i] = new FreeCell(left, top, left + cellWidth, top + cellHeight);
		left += cellWidth + SCREEN_MARGIN;
	}
	for (int i = 4; i < 8; i++)
	{
		mCells[i] = new EndCell(left, top, left + cellWidth, top + cellHeight);
		left += cellWidth + SCREEN_MARGIN;
	}
	left = SCREEN_MARGIN;
	top = top + cellHeight + SCREEN_MARGIN;
	int EXTRA = (MAX_CARDS_PER_CELL-1) * CARD_STAGGER; // FIX this!
	cellHeight = gCardHeight + 2 * CELL_MARGIN + EXTRA;
	for (int i = 8; i < 16; i++)
	{
		mCells[i] = new StartCell(left, top, left + cellWidth, top + cellHeight);
		left += cellWidth + SCREEN_MARGIN;
	}

	// This code shows you how to set an MFC dialog to a desired size:

	// Put this code in OnInitDialog after you've determined minWidth and minHeight
	int minWidth = left; // Set minWidth and minHeight to your needed size
	int minHeight = top + cellHeight + SCREEN_MARGIN;
	CRect neededClient(0, 0, minWidth, minHeight);
	bool menuPresent = true; // set based on whether or not you are using a menu.
	AdjustWindowRectEx(&neededClient, WS_OVERLAPPEDWINDOW, menuPresent, NULL); // converts from client (dialog) to window coordinates
	SetWindowPos(NULL, 0, 0, neededClient.Width(), neededClient.Height(), SWP_NOZORDER | SWP_NOMOVE);

	// make a shuffled deck:
	//	srand((unsigned int)time(0));
	std::vector<int> deck;
	for (int i = 0; i < 52; i++)
		deck.push_back(i);
	for (int i = 0; i < 52; i++)
	{
		int r = rand() % 52;
		int temp = deck[i];
		deck[i] = deck[r];
		deck[r] = temp;
	}

	int index = 0;
	// Put cards in the cells:
	for (int i = 8; i < 12; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mCells[i]->AddCard(deck[index++]);
		}
	}
	for (int i = 12; i < 16; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mCells[i]->AddCard(deck[index++]);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFreecellStarter2020Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFreecellStarter2020Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		DoubleBufferDrawing(dc);

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
		int left = 20;
		int top = 20;
		bool selected = false;
		CPaintDC dc(this); // device context for painting

		//for (int index = 0; index < 52; index++)
		//{
		//	DrawCard(dc, left + index*25, top, index, selected);
		//}
		for (int i = 0; i < 16; i++)
		{
			mCells[i]->Draw(dc);
		}

		CDialogEx::OnPaint();
	}
}

HCURSOR CFreecellStarter2020Dlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

 //This is where you do all your drawing, including setting the background color:
void CFreecellStarter2020Dlg::MyDrawing(CDC& dc)
{
	// Draw the backgroud:
	CRect rcClipBox;
	dc.GetClipBox(rcClipBox);
	COLORREF gcBackgroundColor = (RGB(2, 112, 19)); // your choice!
	dc.FillSolidRect(rcClipBox, gcBackgroundColor);

	// Draw the rest of my stuff:
	int left = 20;
	int top = 20;
	bool selected = false;
	for (int i = 0; i < 16; i++)
	{
		mCells[i]->Draw(dc);
	}
}

// This code you will never change:
void CFreecellStarter2020Dlg::DoubleBufferDrawing(CDC& dc)
{
	// Get clip box
	CRect rcClipBox;
	dc.GetClipBox(rcClipBox);

	// Create memory dc and update it's mapping state
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SetMapMode(dc.GetMapMode());
	memDC.SetViewportOrg(dc.GetViewportOrg());
	memDC.IntersectClipRect(rcClipBox);

	// Create memory bitmap
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rcClipBox.Width(), rcClipBox.Height());
	CBitmap* pOldBmp = memDC.SelectObject(&bmp);

	// Do my Drawings to the memDC backbuffer
	MyDrawing(memDC);

	// Blit memDC to the original dc
	dc.BitBlt(rcClipBox.left, rcClipBox.top, rcClipBox.Width(), rcClipBox.Height(), &memDC, rcClipBox.left, rcClipBox.top, SRCCOPY);

	// Restore old bitmap and cleanup
	memDC.DeleteDC();
	bmp.DeleteObject();
}



void CFreecellStarter2020Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int selected = -1;
	for (int i = 0; i < 16; i++)
	{
		if (mCells[i]->IsClicked(point.x, point.y))
		{
			selected = i;
			break;
		}
	}
	if (selected == -1)
		return;

	if (mFirstClick == -1) // first of two clicks
	{
		if (mCells[selected]->CanRemoveCard()) {
			mFirstClick = selected;
			mCells[selected]->SelectCell(true);
		}
	}
	else // second of two click
	{
		
		// move a card from mFirstClick to selected
		// ONLY if it is legal!
		int top = mCells[mFirstClick]->GetTopCard();
		if (mCells[selected]->CanAddCard(top)) {
			mCells[mFirstClick]->RemoveCard();
			mCells[selected]->AddCard(top);
			mCells[mFirstClick]->SelectCell(false);
		}
		mCells[mFirstClick]->SelectCell(false);
		mFirstClick = -1;
		


		//	if (first < second && goodSuit == true && difference == 1) {
		//		mCells[selected]->AddCard(first);

		//	}
	}

	Invalidate();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CFreecellStarter2020Dlg::OnFileQuit()
{
	// TODO: Add your command handler code here
	EndDialog(IDOK);
}


void CFreecellStarter2020Dlg::OnFileRestart()
{
	// TODO: Add your command handler code here
}


BOOL CFreecellStarter2020Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CFreecellStarter2020Dlg::OnInitMenu(CMenu* pMenu)
{
	CDialogEx::OnInitMenu(pMenu);

	// TODO: Add your message handler code here
}
