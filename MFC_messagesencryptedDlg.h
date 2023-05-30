#pragma once

#include "ServerSocket.h"
#include "ClientSocket.h"

// CMFCmessagesencryptedDlg dialog
class CMFCmessagesencryptedDlg : public CDialogEx
{
// Construction
public:
	CMFCmessagesencryptedDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MESSAGESCRYPTED_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	CServerSocket m_serverSocket;
	CClientSocket m_clientSocket;
	bool m_isServer;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonListen();
	afx_msg void OnBnClickedButtonSend();
	DECLARE_MESSAGE_MAP()

private:
	void AppendToLog(const CString& message);
};
