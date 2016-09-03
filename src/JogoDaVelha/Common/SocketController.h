#pragma once

#include <vector>
#include <thread>
#include "Socket.h"

typedef void (FuncSocketDidConnect)(Socket*);
typedef void (FuncSocketDidDisconnect)(Socket*);
typedef void (FuncSocketDidFailToReceiveData)(Socket*);
typedef void (FuncSocketDidReceiveData)(Socket*, char *buffer, size_t size);

enum SocketType
{
	kSocketTypeServer,
	kSocketTypeClient
};

class SocketController
{
private:

	FuncSocketDidConnect *_socketDidConnectCallback;
	FuncSocketDidDisconnect *_socketDidDisconnectCallback;
	FuncSocketDidFailToReceiveData *_socketDidFailToReceiveDataCallback;
	FuncSocketDidReceiveData *_socketDidReceiveDataCallback;

	bool _initialized;
	bool _winSocketStarted;
	std::thread *_acceptClientsThread;

	Socket *_mainSocket;
	std::vector<Socket*> _sockets;

	SocketController();

	bool init();
	bool initAsServer();
	bool initAsClient();

	void acceptLoop();
	void handleClient(Socket *socket);

	void socketDidConnect(Socket *socket);
	void socketDidDisconnect(Socket *socket);
	void socketDidFailToReceiveData(Socket *socket);
	void socketDidReceiveData(Socket *socket, char *data, size_t size);

public:

	static SocketController *instance();
	~SocketController();

	bool init(SocketType socketType);

	void setSocketDidConnectCallback(FuncSocketDidConnect callback);
	void setSocketDidDisconnectCallback(FuncSocketDidDisconnect callback);
	void setSocketDidReceiveDataCallback(FuncSocketDidReceiveData callback);
	void setSocketDidFailToReceiveDataCallback(FuncSocketDidFailToReceiveData callback);

	bool disconnect(Socket *socket);

	Socket * getMainSocket();
};

