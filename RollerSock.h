#if !defined(AFX_ROLLERSOCK_H__6D052480_2120_11D3_938F_0020781150E8__INCLUDED_)
#define AFX_ROLLERSOCK_H__6D052480_2120_11D3_938F_0020781150E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RollerSock.h : header file
//

class CStatRollDlg;

/////////////////////////////////////////////////////////////////////////////
// CRollerSock command target

class CRollerSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CRollerSock();
	virtual ~CRollerSock();

// Overrides
public:
	char PeekNext();
	void GetLine(CString &str);
	bool CanRecv();
	CRollerSock(CStatRollDlg* m_pDlg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRollerSock)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRollerSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CStatRollDlg* m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLLERSOCK_H__6D052480_2120_11D3_938F_0020781150E8__INCLUDED_)
