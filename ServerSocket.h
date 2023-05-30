#pragma once

// CServerSocket class
class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

	// Overrides
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	// Operations
	bool StartListening(UINT nPort);
	void StopListening();
	void ProcessReceivedMessage(const CString& message);
};
