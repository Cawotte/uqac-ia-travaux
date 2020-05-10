#ifndef AGENT_THREAD_H
#define AGENT_THREAD_H


//------------------------------------------------------------------------
//
//  Name:   AgentThread.h
//
//  Desc:   A wrapper class that makes an Agent runs in its own thread.
//
//------------------------------------------------------------------------

#include "BaseGameEntity.h"
#include <mutex>
#include <condition_variable>

class AgentThread
{

private:


public:

	//The 'main' function of the thread
	void operator()(BaseGameEntity* agent, std::mutex* mutex, std::condition_variable* cv)
	{
		while (true)
		{
			//No update can run at the same time
			std::unique_lock<std::mutex> lockUpdate(*mutex);
			agent->Update();
			lockUpdate.unlock();


			//lock the code
			std::unique_lock<std::mutex> lock(*mutex);
			cv->wait(lock); //Wait here until notified by main thread.
		}
		

	}
};

#endif

