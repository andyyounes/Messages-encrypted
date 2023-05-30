#include "stdafx.h"
#include "ClientSocket.h"

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

void CClientSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		CString receivedData;
		while (Receive(receivedData) > 0)
		{
			// TODO: Process the received data from the server
			// For example, display the received message in a dialog box
			AfxMessageBox(receivedData);

			// Clear the received data buffer
			receivedData.Empty();
		}
	}

	CSocket::OnReceive(nErrorCode);
}

bool CClientSocket::ConnectToServer(const CString& strServerAddress, UINT nServerPort)
{
	if (Create())
	{
		if (Connect(strServerAddress, nServerPort))
			return true;

		Close();
	}

	return false;
}

void CClientSocket::SendMessageToServer(const CString& message)
{
	Send(message);
}
