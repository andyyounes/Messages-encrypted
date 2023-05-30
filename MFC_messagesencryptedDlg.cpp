#include "stdafx.h"
#include "MFC_messagesencrypted.h"
#include "MFC_messagesencryptedDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCmessagesencryptedDlg dialog

CMFCmessagesencryptedDlg::CMFCmessagesencryptedDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_MESSAGESCRYPTED_DIALOG, pParent)
	, m_isServer(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCmessagesencryptedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCmessagesencryptedDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCmessagesencryptedDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CMFCmessagesencryptedDlg::OnBnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCmessagesencryptedDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()

// CMFCmessagesencryptedDlg message handlers

BOOL CMFCmessagesencryptedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCmessagesencryptedDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCmessagesencryptedDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCmessagesencryptedDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCmessagesencryptedDlg::OnBnClickedButtonConnect()
{
	if (!m_isServer)
	{
		CString serverAddress;
		UINT serverPort;
		GetDlgItemText(IDC_EDIT_SERVER_ADDRESS, serverAddress);
		serverPort = GetDlgItemInt(IDC_EDIT_SERVER_PORT);

		if (m_clientSocket.ConnectToServer(serverAddress, serverPort))
		{
			AppendToLog(_T("Connected to the server."));
		}
		else
		{
			AppendToLog(_T("Failed to connect to the server."));
		}
	}
}

void CMFCmessagesencryptedDlg::OnBnClickedButtonListen()
{
	if (!m_isServer)
	{
		UINT serverPort;
		serverPort = GetDlgItemInt(IDC_EDIT_SERVER_PORT);

		if (m_serverSocket.Create(serverPort))
		{
			if (m_serverSocket.Listen())
			{
				AppendToLog(_T("Listening for incoming connections..."));
				m_isServer = true;
			}
			else
			{
				AppendToLog(_T("Failed to listen on the specified port."));
			}
		}
		else
		{
			AppendToLog(_T("Failed to create the server socket."));
		}
	}
}

void CMFCmessagesencryptedDlg::OnBnClickedButtonSend()
{
	if (m_isServer)
	{
		CString message;
		GetDlgItemText(IDC_EDIT_MESSAGE, message);

		if (m_serverSocket.SendAllClients(message))
		{
			AppendToLog(_T("Message sent to all clients."));
		}
		else
		{
			AppendToLog(_T("Failed to send message to clients."));
		}
	}
	else
	{
		CString message;
		GetDlgItemText(IDC_EDIT_MESSAGE, message);

		if (m_clientSocket.IsConnected())
		{
			m_clientSocket.SendMessageToServer(message);
			AppendToLog(_T("Message sent to the server."));
		}
		else
		{
			AppendToLog(_T("Not connected to any server."));
		}
	}
}

void CMFCmessagesencryptedDlg::AppendToLog(const CString& message)
{
	CString log;
	GetDlgItemText(IDC_EDIT_LOG, log);

	log += message + _T("\r\n");
	SetDlgItemText(IDC_EDIT_LOG, log);
}
