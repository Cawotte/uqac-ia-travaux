#ifndef CONSOLE_UTILS_THREAD_SAFE_H
#define CONSOLE_UTILS_THREAD_SAFE_H

#include <mutex>

#include <iostream>
#include <memory>
#include <windows.h>
//------------------------------------------------------------------------
//
//  Name:   EntityManager.h
//
//  Desc:   Singleton class that provide basic output write with thread-safety.
//
//------------------------------------------------------------------------

//provide easy access
#define CoutSafe ConsoleUtilsThreadSafe::Instance()

class ConsoleUtilsThreadSafe
{
private:

	static ConsoleUtilsThreadSafe* m_instance;

	//shared mutex to ensure thread-safety
	std::mutex m_mtx_cmd;

	//hidden constructor for singleton pattern
	ConsoleUtilsThreadSafe() {};
	~ConsoleUtilsThreadSafe() {};


	//private for singleton purposes
	ConsoleUtilsThreadSafe(const ConsoleUtilsThreadSafe&) = delete;
	ConsoleUtilsThreadSafe& operator=(const ConsoleUtilsThreadSafe&) = delete;

	//default text colors can be found in wincon.h
	inline void SetTextColor(WORD colors)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, colors);
	}

public:

	//Singleton pattern
	static ConsoleUtilsThreadSafe& Instance();



	//Thread-safe couts

	template <typename T>
	void PrintThreadSafe(T&& arg, 
		WORD colors = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN)
	{
		std::lock_guard<std::mutex> lock(m_mtx_cmd);
		SetTextColor(colors);
		std::cout << arg << std::endl;
	}

	template <typename T, typename T2>
	void PrintThreadSafe(T&& arg1, T2&& arg2, 
		WORD colors = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN)
	{
		std::lock_guard<std::mutex> lock(m_mtx_cmd);
		SetTextColor(colors);
		std::cout << arg1 << arg2 << std::endl;
	}


	template <typename T, typename T2, typename T3>
	void PrintThreadSafe(T&& arg1, T2&& arg2, T3&& arg3, 
		WORD colors = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN)
	{
		std::lock_guard<std::mutex> lock(m_mtx_cmd);
		SetTextColor(colors);
		std::cout << arg1 << arg2 << arg3 << std::endl;
	}


	template <typename T, typename T2, typename T3, typename T4>
	void PrintThreadSafe(T&& arg1, T2&& arg2, T3&& arg3, T4&& arg4, 
		WORD colors = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN)
	{
		std::lock_guard<std::mutex> lock(m_mtx_cmd);
		SetTextColor(colors);
		std::cout << arg1 << arg2 << arg3 << arg4 << std::endl;
	}
};


#endif
