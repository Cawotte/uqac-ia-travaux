#include "ConsoleUtilsThreadSafe.h"


ConsoleUtilsThreadSafe& ConsoleUtilsThreadSafe::Instance()
{
	//Singleton
	//apparently thread-safe and cleaned up on itw own
	static ConsoleUtilsThreadSafe instance;
	return instance;
}

void ConsoleUtilsThreadSafe::SetTextColor(WORD colors)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, colors);
}

