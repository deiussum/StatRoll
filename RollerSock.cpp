// RollerSock.cpp : implementation file
//

#include "stdafx.h"
#include "StatRoll.h"
#include "RollerSock.h"
#include "StatRollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRollerSock

CRollerSock::CRollerSock()
{
}

CRollerSock::~CRollerSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRollerSock, CSocket)
	//{{AFX_MSG_MAP(CRollerSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRollerSock member functions

CRollerSock::CRollerSock(CStatRollDlg *pDlg)
:m_pDlg(pDlg)
{
	
}



void CRollerSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	while (CanRecv())
	{
		DWORD dwBytes;

		IOCtl(FIONREAD, &dwBytes);

		if (dwBytes == 0)
		{
			m_pDlg->OnSocketClose();
			break;
		}
		else
		{
			m_pDlg->OnRecv();
		}
	}

	CSocket::OnReceive(nErrorCode);
}

bool CRollerSock::CanRecv()
{
	FD_SET sockSet;
	TIMEVAL timeVal = {0, 0};

	FD_ZERO(&sockSet);
	FD_SET(m_hSocket, &sockSet);
	
	select(NULL, &sockSet, NULL, NULL, &timeVal);

	return FD_ISSET(m_hSocket, &sockSet) !=0;
}

void CRollerSock::GetLine(CString &str)
{
	char ch, next;

	str = "";

	while (CanRecv())
	{
		DWORD dwBytes;

		IOCtl(FIONREAD, &dwBytes);

		if (dwBytes == 0)
		{
			Close();
			return;
		}

		Receive(&ch, 1);
		str += ch;

		if (ch == '\r' || ch == '\n')
			break;
	}
	
	next = PeekNext();

	if (next == '\r' || next == '\n')
	{
		Receive(&ch, 1);
		str+=ch;
	}
}

void CRollerSock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDlg->AddText("Socket disconnected\r\n");
	m_pDlg->m_szStatus = "Disconnected";
	m_pDlg->m_bConnected = FALSE;
	m_pDlg->m_ctrlConnect.EnableWindow(TRUE);
	m_pDlg->m_ctrlDisconnect.EnableWindow(FALSE);
	m_pDlg->UpdateData(FALSE);
	
	CSocket::OnClose(nErrorCode);
}

char CRollerSock::PeekNext()
{
	char rChar = NULL;

	if (CanRecv())
	{
		Receive(&rChar, 1, MSG_PEEK);
	}

	return rChar;
}
