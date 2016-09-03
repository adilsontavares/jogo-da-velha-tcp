#pragma once

#include <vector>
#include "Socket.h"

#define FuncSocketWasDisconnected(name)			(void (&(name))(Socket*))
#define FuncSocketFailedToReceiveData(name)		(void (&(name))(Socket*))
#define FuncSocketDidReceivData(name)			(void (&(name))(Socket*))

enum SocketType
{
	kSocketTypeServer,
	kSocketTypeClient
};

class SocketController
{
private:

	FuncSocketWasDisconnected(_socketWasDisconnectedCallback);
	FuncSocketFailedToReceiveData(_socketFailedToReceiveDataCallback);
	FuncSocketDidReceivData(_socketDidReceiveDataCallback);

	bool _initialized;
	bool _winSocketStarted;
	thread *_acceptClientsThread;

	Socket *_mainSocket;
	std::vector<Socket*> _sockets;

	SocketController();

	bool init();
	bool initAsServer();
	bool initAsClient();

	void acceptLoop();
	void handleClient(Socket *socket);

	void socketWasDisconnected(Socket *socket);
	void socketFailedToReceiveData(Socket *socket);
	void socketDidReceiveData(Socket *socket, char *data, size_t size);

public:

	static SocketController *instance();

	bool init(SocketType socketType);
};

