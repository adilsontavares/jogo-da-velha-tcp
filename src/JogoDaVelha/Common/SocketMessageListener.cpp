#include "SocketMessageListener.h"
#include "SocketController.h"
#include "Error.h"
#include "Console.h"

using namespace std;
using namespace std::placeholders;

SocketMessageListener::SocketMessageListener()
{
	_initialized = false;
}
SocketMessageListener::~SocketMessageListener()
{
}

SocketMessageListener * SocketMessageListener::instance()
{
	static SocketMessageListener *instance = 0;
	if (!instance)
		instance = new SocketMessageListener();
	return instance;
}

void SocketMessageListener::init()
{
	Error::assert(!_initialized, "SocketMessageListener is already initialized.");

	SocketController *socketController = SocketController::instance();
	socketController->setSocketDidReceiveDataCallback(bind(&SocketMessageListener::onReceiveSocketData, this, _1, _2, _3));

	_initialized = true;
}

void SocketMessageListener::registerMessage(SocketMessageCode code, FuncRegisterSocketMessage callback)
{
	auto it = _messages.find(code);
	if (it != _messages.end())
	{
		Console::error("Could not register message callback because code %u is already mapped.", code);
		return;
	}

	_messages[code] = callback;
}

void SocketMessageListener::onReceiveSocketData(Socket * socket, char * buffer, size_t size)
{
	SocketMessage *message = new SocketMessage(buffer, size);
	auto it = _messages.find(message->getCode());

	if (it == _messages.end())
		Console::log("Socket received an unregistered message for code %d", message->getCode());
	else
		it->second(socket, message);
}

