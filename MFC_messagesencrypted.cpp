#include "stdafx.h"
#include "MFC_messagesencrypted.h"
#include "MFC_messagesencryptedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMFCmessagesencryptedApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CMFCmessagesencryptedApp::CMFCmessagesencryptedApp()
{
}

CMFCmessagesencryptedApp theApp;
BOOL CMFCmessagesencryptedApp::InitInstance()
{
    CWinApp::InitInstance();

    AfxEnableControlContainer();

    CMFCmessagesencryptedDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    
 if (nResponse == IDOK)
{
    // Retrieve the entered username and password
    CString username = dlg.GetUsername();
    CString password = dlg.GetPassword();

    // Check if the username and password are valid
    if (username == "admin" && password == "password")
    {
        // If valid, display a success message
        AfxMessageBox(_T("Login successful!"));
    }
    else
    {
        // If invalid, display an error message
        AfxMessageBox(_T("Invalid username or password. Please try again."));
    }
}

else if (nResponse == IDCANCEL)
{
    // Display a message indicating cancellation
    AfxMessageBox(_T("Dialog canceled."));
    // Perform any necessary cleanup or additional actions before closing the dialog
    // ...
}
    return FALSE;
}
