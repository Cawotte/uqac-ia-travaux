#include "ConsoleUtilsThreadSafe.h"


ConsoleUtilsThreadSafe& ConsoleUtilsThreadSafe::Instance()
{
	//Singleton
	//apparently thread-safe and cleaned up on itw own
	static ConsoleUtilsThreadSafe instance;
	return instance;
}


