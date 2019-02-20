// StatRoll.h : main header file for the STATROLL application
//

#if !defined(AFX_STATROLL_H__04E72D24_2117_11D3_938F_0020781150E8__INCLUDED_)
#define AFX_STATROLL_H__04E72D24_2117_11D3_938F_0020781150E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatRollApp:
// See StatRoll.cpp for the implementation of this class
//

class CStatRollApp : public CWinApp
{
public:
	CStatRollApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatRollApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStatRollApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATROLL_H__04E72D24_2117_11D3_938F_0020781150E8__INCLUDED_)
