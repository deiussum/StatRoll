// StatRollDlg.h : header file
//

#if !defined(AFX_STATROLLDLG_H__04E72D26_2117_11D3_938F_0020781150E8__INCLUDED_)
#define AFX_STATROLLDLG_H__04E72D26_2117_11D3_938F_0020781150E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStatRollDlg dialog

#include "RollerSock.h"

const int STAT_STR = 1;
const int STAT_INT = 2;
const int STAT_WIS = 3;
const int STAT_DEX = 4;
const int STAT_CON = 5;
const int STAT_OTHR = 6;

const int MAX_LINE = 512;

class CStatRollDlg : public CDialog
{
public:
	CRollerSock* m_Socket;
	CString m_szAcceptFile;

// Construction
public:
	void SetTotalColor();
	~CStatRollDlg();
	BOOL m_bConnected;
	void SendFile();
	void LoadParseStrings();
	void CheckStats();
	bool CompareStrings(CString parser, CString input, int &val, int &stat);
	bool ParseLine(LPCTSTR line);
	void OnRecv();
	void AddText(CString str);
	void OnSocketClose();
	CStatRollDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStatRollDlg)
	enum { IDD = IDD_STATROLL_DIALOG };
	CButton	m_ctrlDisconnect;
	CButton	m_ctrlConnect;
	CEdit	m_ctrlCurStr;
	CEdit	m_ctrlCurInt;
	CEdit	m_ctrlCurWis;
	CEdit	m_ctrlCurDex;
	CEdit	m_ctrlCurCon;
	CEdit	m_ctrlCurOth;
	CEdit	m_ctrlCurMax;
	CEdit	m_ctrlTotal;
	CButton	m_ctrlDiscard;
	CButton	m_ctrlAccept;
	CComboBox	m_ctrlParse;
	CEdit	m_ctrlOutput;
	UINT	m_nStrMax;
	UINT	m_nIntMax;
	UINT	m_nWisMax;
	UINT	m_nDexMax;
	UINT	m_nConMax;
	UINT	m_nOthrMax;
	UINT	m_nStrWant;
	UINT	m_nIntWant;
	UINT	m_nWisWant;
	UINT	m_nDexWant;
	UINT	m_nConWant;
	UINT	m_nOthrWant;
	UINT	m_nMaxWant;
	UINT	m_nMaxMax;
	UINT	m_nStrCur;
	UINT	m_nIntCur;
	UINT	m_nWisCur;
	UINT	m_nDexCur;
	UINT	m_nConCur;
	UINT	m_nOthrCur;
	UINT	m_nMaxCur;
	CString	m_szServer;
	UINT	m_nPort;
	CString	m_szInput;
	CString	m_szParse;
	BOOL	m_bInt;
	BOOL	m_bWis;
	BOOL	m_bDex;
	BOOL	m_bCon;
	BOOL	m_bOthr;
	BOOL	m_bMax;
	BOOL	m_bStr;
	CString	m_szStatus;
	UINT	m_nTotalRoll;
	BOOL	m_bAutoAccept;
	BOOL	m_bSendFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatRollDlg)
	public:
	virtual void OnSetFont(CFont* pFont);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	

	// Generated message map functions
	//{{AFX_MSG(CStatRollDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnSend();
	afx_msg void OnButtondiscard();
	afx_msg void OnButtonaccpt();
	afx_msg void OnDisconnect();
	afx_msg void OnSelectFile();
	afx_msg void OnFileAccept();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRollHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_fntBold;
public:
	afx_msg void OnTimer(UINT nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATROLLDLG_H__04E72D26_2117_11D3_938F_0020781150E8__INCLUDED_)
