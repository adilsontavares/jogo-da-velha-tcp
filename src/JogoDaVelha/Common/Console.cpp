#include "Console.h"
#include <iostream>
#include <stdarg.h>
#include <fstream>
#include <string>

using namespace std;

void Console::log(const char * format, ...)
{
	printf("LOG: ");

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\n");
}

void Console::warning(const char * format, ...)
{
	printf("WARNING: ");

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\n");
}

void Console::error(const char * format, ...)
{
	printf("ERROR: ");

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\n");
}

void Console::write(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void Console::writeLine(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\n");
}

void Console::clear()
{
	system("cls");
}

std::string Console::readLine()
{
	string line;
	getline(cin, line);
	return line;
}
