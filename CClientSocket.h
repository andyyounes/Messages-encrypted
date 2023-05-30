#pragma once

// CClientSocket class
class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	// Overrides
	virtual void OnReceive(int nErrorCode);

	// Operations
	bool ConnectToServer(const CString& strServerAddress, UINT nServerPort);
	void SendMessageToServer(const CString& message);
};
