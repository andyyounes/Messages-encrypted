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

bool CClient
