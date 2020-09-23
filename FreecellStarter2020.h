
// FreecellStarter2020.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFreecellStarter2020App:
// See FreecellStarter2020.cpp for the implementation of this class
//

class CFreecellStarter2020App : public CWinApp
{
public:
	CFreecellStarter2020App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFreecellStarter2020App theApp;
