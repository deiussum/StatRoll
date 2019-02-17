// StatRollDlg.cpp : implementation file
//

#include "stdafx.h"
#include <sstream>
#include <fstream>
#include <mmsystem.h>
#include "StatRoll.h"
#include "StatRollDlg.h"
#include ".\statrolldlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatRollDlg dialog

CStatRollDlg::CStatRollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatRollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatRollDlg)
	m_nStrMax = 0;
	m_nIntMax = 0;
	m_nWisMax = 0;
	m_nDexMax = 0;
	m_nConMax = 0;
	m_nOthrMax = 0;
	m_nStrWant = 8;
	m_nIntWant = 8;
	m_nWisWant = 8;
	m_nDexWant = 8;
	m_nConWant = 8;
	m_nOthrWant = 8;
	m_nMaxWant = 80;
	m_nMaxMax = 0;
	m_nStrCur = 0;
	m_nIntCur = 0;
	m_nWisCur = 0;
	m_nDexCur = 0;
	m_nConCur = 0;
	m_nOthrCur = 0;
	m_nMaxCur = 0;
	m_szServer = _T("carrionfields.net");
	m_nPort = 4449;
	m_szInput = _T("");
	m_szParse = _T("");
	m_bInt = TRUE;
	m_bWis = TRUE;
	m_bDex = TRUE;
	m_bCon = TRUE;
	m_bOthr = FALSE;
	m_bMax = TRUE;
	m_bStr = TRUE;
	m_szStatus = _T("Ready");
	m_nTotalRoll = 0;
	m_bAutoAccept = FALSE;
	m_bSendFile = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Socket = NULL;
	m_bConnected = FALSE;
}

void CStatRollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatRollDlg)
	DDX_Control(pDX, IDC_DISCONNECT, m_ctrlDisconnect);
	DDX_Control(pDX, IDC_CONNECT, m_ctrlConnect);
	DDX_Control(pDX, IDC_STRCUR, m_ctrlCurStr);
	DDX_Control(pDX, IDC_INTCUR, m_ctrlCurInt);
	DDX_Control(pDX, IDC_WISCUR, m_ctrlCurWis);
	DDX_Control(pDX, IDC_DEXCUR, m_ctrlCurDex);
	DDX_Control(pDX, IDC_CONCUR, m_ctrlCurCon);
	DDX_Control(pDX, IDC_OTHRCUR, m_ctrlCurOth);
	DDX_Control(pDX, IDC_MAXCUR, m_ctrlCurMax);
	DDX_Control(pDX, IDC_MAXWANT, m_ctrlTotal);
	DDX_Control(pDX, IDC_BUTTONDISCARD, m_ctrlDiscard);
	DDX_Control(pDX, IDC_BUTTONACCPT, m_ctrlAccept);
	DDX_Control(pDX, IDC_PARSE, m_ctrlParse);
	DDX_Control(pDX, IDC_OUTPUT, m_ctrlOutput);
	DDX_Text(pDX, IDC_STRMAX, m_nStrMax);
	DDX_Text(pDX, IDC_INTMAX, m_nIntMax);
	DDX_Text(pDX, IDC_WISMAX, m_nWisMax);
	DDX_Text(pDX, IDC_DEXMAX, m_nDexMax);
	DDX_Text(pDX, IDC_CONMAX, m_nConMax);
	DDX_Text(pDX, IDC_OTHRMAX, m_nOthrMax);
	DDX_Text(pDX, IDC_STRWANT, m_nStrWant);
	DDX_Text(pDX, IDC_INTWANT, m_nIntWant);
	DDX_Text(pDX, IDC_WISWANT, m_nWisWant);
	DDX_Text(pDX, IDC_DEXWANT, m_nDexWant);
	DDX_Text(pDX, IDC_CONWANT, m_nConWant);
	DDX_Text(pDX, IDC_OTHRWANT, m_nOthrWant);
	DDX_Text(pDX, IDC_MAXWANT, m_nMaxWant);
	DDX_Text(pDX, IDC_MAXMAX, m_nMaxMax);
	DDX_Text(pDX, IDC_STRCUR, m_nStrCur);
	DDX_Text(pDX, IDC_INTCUR, m_nIntCur);
	DDX_Text(pDX, IDC_WISCUR, m_nWisCur);
	DDX_Text(pDX, IDC_DEXCUR, m_nDexCur);
	DDX_Text(pDX, IDC_CONCUR, m_nConCur);
	DDX_Text(pDX, IDC_OTHRCUR, m_nOthrCur);
	DDX_Text(pDX, IDC_MAXCUR, m_nMaxCur);
	DDX_Text(pDX, IDC_SERVER, m_szServer);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Text(pDX, IDC_INPUT, m_szInput);
	DDX_CBString(pDX, IDC_PARSE, m_szParse);
	DDX_Check(pDX, IDC_CHECKINT, m_bInt);
	DDX_Check(pDX, IDC_CHECKWIS, m_bWis);
	DDX_Check(pDX, IDC_CHECKDEX, m_bDex);
	DDX_Check(pDX, IDC_CHECKCON, m_bCon);
	DDX_Check(pDX, IDC_CHECKOTHER, m_bOthr);
	DDX_Check(pDX, IDC_CHECKMAX, m_bMax);
	DDX_Check(pDX, IDC_CHECKSTR, m_bStr);
	DDX_Text(pDX, IDC_STATUS, m_szStatus);
	DDX_Text(pDX, IDC_TOTALROLLS, m_nTotalRoll);
	DDX_Check(pDX, IDC_AUTOACCEPT, m_bAutoAccept);
	DDX_Check(pDX, IDC_FILEACCEPT, m_bSendFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatRollDlg, CDialog)
	//{{AFX_MSG_MAP(CStatRollDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_BUTTONDISCARD, OnButtondiscard)
	ON_BN_CLICKED(IDC_BUTTONACCPT, OnButtonaccpt)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_SELECTFILE, OnSelectFile)
	ON_BN_CLICKED(IDC_FILEACCEPT, OnFileAccept)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ROLLHELP, OnRollHelp)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatRollDlg message handlers

BOOL CStatRollDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	m_Socket = new CRollerSock(this);

	m_fntBold.CreateFont(16, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,
		"Times New Roman");

	m_bConnected= FALSE;
	m_szAcceptFile="";
	LoadParseStrings();

	SetTimer(1, 250, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStatRollDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStatRollDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}

//	SetTotalColor();

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStatRollDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStatRollDlg::OnSocketClose()
{
	AddText("Server disconnected");
	m_Socket->Close();
	m_bConnected = FALSE;
}

void CStatRollDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (m_bConnected)
	{
		m_Socket->ShutDown();
		m_Socket->Close();
	}

	m_Socket->Create();

	m_szStatus = "Connecting please hold...";
	UpdateData(FALSE);

	m_ctrlConnect.EnableWindow(FALSE);

	if (m_Socket->Connect(m_szServer, m_nPort))
	{
		AddText("Successfully connected\r\n");
		m_szStatus = "Connected";
		m_bConnected = TRUE;
		m_ctrlDisconnect.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlConnect.EnableWindow(TRUE);
		m_bConnected = FALSE;
		m_szStatus = "Failed to connect";
		m_Socket->Close();

	}

	UpdateData(FALSE);
}

void CStatRollDlg::AddText(CString str)
{
	int numLines = m_ctrlOutput.GetLineCount();

	int index = m_ctrlOutput.LineIndex(numLines-1);
	int lineLen = m_ctrlOutput.LineLength(index);

	if (lineLen > 0)
	{
		OutputDebugString("Test");
	}
		
	
	index += lineLen;

	// Make sure CRLF is correct
	str.Replace("\n\r", "CRLF");
//	str.Replace("\r\n", "CRLF");
	str.Replace("\r", "CRLF");
	str.Replace("\n", "CRLF");
//	if (str.Find("CRLF", 0) == -1)
//		str += "CRLF";

	str.Replace("CRLF", "\r\n");

	m_ctrlOutput.SetSel(index, index);
	m_ctrlOutput.ReplaceSel(str);

}

void CStatRollDlg::OnRecv()
{
	CString str;

	m_Socket->GetLine(str);

	if (!ParseLine(str))
		AddText(str);
	else
		CheckStats();
}

bool CStatRollDlg::ParseLine(LPCTSTR line)
{
	UpdateData();
	
	char inBuffer[MAX_LINE];
	char parseBuffer[MAX_LINE];

	char inWord[MAX_LINE];
	char parseWord[MAX_LINE];
	
	bool parsed = FALSE;
	int stat, statVal;

	strcpy(inBuffer, line);
	strcpy(parseBuffer, m_szParse);

	istringstream inStream(inBuffer, strlen(inBuffer));
	istringstream parseStream(parseBuffer, strlen(parseBuffer));

	if (!inStream || !parseStream)
		return FALSE;

	while (inStream >> inWord && parseStream >> parseWord)
	{
		if (!CompareStrings(parseWord, inWord, statVal, stat))
		{
			parsed = FALSE;
			break;
		}
		
		parsed = TRUE;
		switch (stat)
		{
		case STAT_STR:
			m_nStrCur = statVal;
			break;
		case STAT_INT:
			m_nIntCur = statVal;
			break;
		case STAT_WIS:
			m_nWisCur = statVal;
			break;
		case STAT_DEX:
			m_nDexCur = statVal;
			break;
		case STAT_CON:
			m_nConCur = statVal;
			break;
		case STAT_OTHR:
			m_nOthrCur = statVal;
			break;
		}
	}
	
		
	if (parsed)
	{
		UpdateData(FALSE);
		return TRUE;
	}
	else
		return FALSE;

}

void CStatRollDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!m_Socket)
		return;

	m_szInput += "\r\n";

	m_Socket->Send(m_szInput, m_szInput.GetLength());
	AddText(m_szInput);

	m_szInput = "";
	UpdateData(FALSE);
}



bool CStatRollDlg::CompareStrings(CString parser, CString input, int &val,
								  int &stat)
{
	int nParse = 0, nIn;

	val = 0;
	stat = 0;

	if (parser.CompareNoCase(input) == 0)
		return TRUE;

	nParse = parser.Find("%");

	if (nParse < 0 || input.GetLength() < nParse)
		return FALSE;

	CString r1 = parser.Left(nParse);
	CString r2 = input.Left(nParse);
	CString s = parser.Mid(nParse);
	s = s.Left(4);
	CString s2 = input.Mid(nParse);
	
	val = atoi(s2);
	if (val == 0)
		return FALSE;

	if (val < 10)
		nIn = 1;
	else 
		nIn = 2;
	CString t1 = parser.Mid(nParse + 4);
	CString t2 = input.Mid(nParse + nIn);
	
	if (r1.CompareNoCase(r2) != 0)
		return FALSE;
	if (t1.CompareNoCase(t2) != 0)
		return FALSE;
	
	if (s.CompareNoCase("%str") == 0)
		stat = STAT_STR;
	if (s.CompareNoCase("%int") == 0)
		stat = STAT_INT;
	if (s.CompareNoCase("%wis") == 0)
		stat = STAT_WIS;
	if (s.CompareNoCase("%dex") == 0)
		stat = STAT_DEX;
	if (s.CompareNoCase("%con") == 0)
		stat = STAT_CON;
	if (s.CompareNoCase("%oth") == 0)
		stat = STAT_OTHR;


	return TRUE;
}

void CStatRollDlg::CheckStats()
{
	UpdateData();

	m_nTotalRoll++;

	if (m_nWisCur > m_nWisMax)
		m_nWisMax = m_nWisCur;
	if (m_nIntCur > m_nIntMax)
		m_nIntMax = m_nIntCur;
	if (m_nStrCur > m_nStrMax)
		m_nStrMax = m_nStrCur;
	if (m_nDexCur > m_nDexMax)
		m_nDexMax = m_nDexCur;
	if (m_nConCur > m_nConMax)
		m_nConMax = m_nConCur;
	if (m_nOthrCur > m_nOthrMax)
		m_nOthrMax = m_nOthrCur;

	int total=0;

	if (m_bStr)
		total += m_nStrCur;
	if (m_bInt)
		total += m_nIntCur;
	if (m_bWis)
		total += m_nWisCur;
	if (m_bDex)
		total += m_nDexCur;
	if (m_bCon)
		total += m_nConCur;
	if (m_bOthr)
		total += m_nOthrCur;

	m_nMaxCur = total;

	if (m_nMaxCur > m_nMaxMax)
		m_nMaxMax = m_nMaxCur;

	BOOL found = TRUE;

	if (m_bStr && m_nStrCur < m_nStrWant)
		found = FALSE;
	if (m_bInt && m_nIntCur < m_nIntWant)
		found = FALSE;
	if (m_bWis && m_nWisCur < m_nWisWant)
		found = FALSE;
	if (m_bDex && m_nDexCur < m_nDexWant)
		found = FALSE;
	if (m_bCon && m_nConCur < m_nConWant)
		found = FALSE;
	if (m_bOthr && m_nOthrCur < m_nOthrWant)
		found = FALSE;
	if (m_bMax && m_nMaxCur < m_nMaxWant)
		found = FALSE;

	if (!found)
	{
		m_Socket->Send("n\r\n", 3);
		m_szStatus = "Rolling...";
	}
	else
	{
		m_ctrlDiscard.EnableWindow(TRUE);
		m_ctrlAccept.EnableWindow(TRUE);
		if (m_bAutoAccept)
		{
			m_Socket->Send("y\r\n", 3);
			m_szStatus = "Roll accepted";
			UpdateData(FALSE);
			if (m_bSendFile)
				SendFile();
		}
		else
			m_szStatus = "Keep roll?";

		PlaySound("gong.wav", NULL, SND_FILENAME | SND_ASYNC);
	}

	UpdateData(FALSE);

}


void CStatRollDlg::LoadParseStrings()
{
	CString line;
	CStdioFile file;

	if (!file.Open("settings.txt", CFile::modeRead))
	{
		AfxMessageBox("Failed to load settings.txt");
		return;
	}

	file.ReadString(line);
	m_szServer = line;
	file.ReadString(line);
	m_nPort = atoi(line);

	while (file.ReadString(line))
	{
		UINT pos = m_ctrlParse.GetCount();

		m_ctrlParse.InsertString(pos, line);
	}
	UpdateData(FALSE);

	m_ctrlParse.SetCurSel(0);
}

void CStatRollDlg::OnButtondiscard() 
{
	// TODO: Add your control notification handler code here
	m_Socket->Send("n\r\n", 3);
	m_ctrlDiscard.EnableWindow(FALSE);
	m_ctrlAccept.EnableWindow(FALSE);
}

void CStatRollDlg::OnButtonaccpt() 
{
	// TODO: Add your control notification handler code here
	m_Socket->Send("y\r\n", 3);
	m_ctrlDiscard.EnableWindow(FALSE);
	m_ctrlAccept.EnableWindow(FALSE);
	m_szStatus = "Roll accepted";
	UpdateData(FALSE);

	if (m_bSendFile)
		SendFile();

}

void CStatRollDlg::OnDisconnect() 
{
	m_Socket->ShutDown();
	m_Socket->Close();

	m_ctrlConnect.EnableWindow(TRUE);
	m_ctrlDisconnect.EnableWindow(FALSE);

}

void CStatRollDlg::OnSelectFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_szAcceptFile = dlg.GetPathName();
	}
}

void CStatRollDlg::SendFile()
{
	m_szStatus="Sending text file";
	UpdateData(FALSE);

	ifstream file(m_szAcceptFile);
	CString line;
	char buffer[128];

	while (file.getline(buffer, 128))
	{
		line = buffer;
		line += "\r\n";
		m_Socket->Send(line, line.GetLength());
	}
	
	m_szStatus="File sent";
	UpdateData(FALSE);
}

void CStatRollDlg::OnFileAccept() 
{
	// TODO: Add your control notification handler code here
	if (m_szAcceptFile == "")
		OnSelectFile();
}

CStatRollDlg::~CStatRollDlg()
{
	if (m_Socket)
		delete m_Socket;
}

HBRUSH CStatRollDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	CFont* old;

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd == &m_ctrlTotal)
		{
			old = pDC->SelectObject(&m_fntBold);

			//old->DeleteObject();
		}
	}

	if (pWnd == &m_ctrlCurMax || pWnd == &m_ctrlCurOth ||
		pWnd == &m_ctrlCurCon || pWnd == &m_ctrlCurDex ||
		pWnd == &m_ctrlCurWis || pWnd == &m_ctrlCurInt ||
		pWnd == &m_ctrlCurStr)
	{
		old = pDC->SelectObject(&m_fntBold);

		//old->DeleteObject();
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CStatRollDlg::OnRollHelp() 
{
	// TODO: Add your control notification handler code here
	PROCESS_INFORMATION info;
	STARTUPINFO start;

	ZeroMemory(&start, sizeof(STARTUPINFO));
	start.cb = sizeof(STARTUPINFO);
	//start.dwFlags

	CreateProcess(NULL, "Winhelp statroll.hlp", NULL,
		NULL, FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &start, &info);
}

void CStatRollDlg::SetTotalColor()
{
	// NOTE:  This routine is not working yet
	UINT total=0;
	CDC* pDC = m_ctrlTotal.GetDC();

	if (m_bStr)
		total += m_nStrCur;
	if (m_bInt)
		total += m_nIntCur;
	if (m_bWis)
		total += m_nWisCur;
	if (m_bDex)
		total += m_nDexCur;
	if (m_bCon)
		total += m_nConCur;
	if (m_bOthr)
		total += m_nOthrCur;

	if (total > m_nMaxWant)
		pDC->SetTextColor(RGB(255, 0, 0));
	else
		pDC->SetTextColor(RGB(0, 0, 255));

	m_ctrlTotal.ReleaseDC(pDC);
}




void CStatRollDlg::OnSetFont(CFont* pFont) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::OnSetFont(pFont);
}

void CStatRollDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (this->m_bConnected && m_Socket->CanRecv())
	{
		OnRecv();
	}

	CDialog::OnTimer(nIDEvent);
}
