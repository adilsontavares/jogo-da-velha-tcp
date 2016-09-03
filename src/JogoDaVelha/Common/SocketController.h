#pragma once

#include <vector>
#include <thread>
#include <functional>
#include "Socket.h"

typedef std::function<void(Socket*)> FuncSocketDidConnect;
typedef std::function<void(Socket*)> FuncSocketDidDisconnect;
typedef std::function<void(Socket*)> FuncSocketDidFailToReceiveData;
typedef std::function<void(Socket*, char*, size_t)> FuncSocketDidReceiveData;

enum SocketType
{
	kSocketTypeServer,
	kSocketTypeClient
};

class SocketController
{
private:

	FuncSocketDidConnect _socketDidConnectCallback;
	FuncSocketDidDisconnect _socketDidDisconnectCallback;
	FuncSocketDidFailToReceiveData _socketDidFailToReceiveDataCallback;
	FuncSocketDidReceiveData _socketDidReceiveDataCallback;

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

