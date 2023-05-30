#include "stdafx.h"
#include "ServerSocket.h"

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::OnAccept(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		// Accept the incoming connection
		CSocket clientSocket;
		if (Accept(clientSocket))
		{
			// Process the new connection
			CString ipAddress;
			UINT port;
			clientSocket.GetPeerName(ipAddress, port);

			CString message;
			message.Format(_T("Accepted connection from %s:%u"), ipAddress, port);
			AfxMessageBox(message);

			// Receive data from the client
			CString receivedData;
			while (clientSocket.Receive(receivedData) > 0)
			{
				// Process the received message
				ProcessReceivedMessage(receivedData);

				// Clear the received data buffer
				receivedData.Empty();
			}

			// Close the client socket
			clientSocket.Close();
		}
	}

	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		CString receivedData;
		while (Receive(receivedData) > 0)
		{
			// Process the received message
			ProcessReceivedMessage(receivedData);

			// Clear the received data buffer
			receivedData.Empty();
		}
	}

	CSocket::OnReceive(nErrorCode);
}

bool CServerSocket::StartListening(UINT nPort)
{
	if (Create(nPort))
	{
		if (Listen())
			return true;

		Close();
	}

	return false;
}

void CServerSocket::StopListening()
{
	Close();
}

void CServerSocket::ProcessReceivedMessage(const CString& message)
{
	// TODO: Implement your logic to process the received message
	// For example, display the received message in a dialog box
	AfxMessageBox(message);
}
