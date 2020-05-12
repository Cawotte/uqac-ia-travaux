#include "MultithreadManager.h"

#include "misc/ConsoleUtils.h" //Sleep
#include "MessageDispatcher.h"

//print thread-safe
#include "ConsoleUtilsThreadSafe.h"

void MultithreadManager::StartThread(BaseGameEntity* entity, int nbIterations)
{
	int nbThreads = m_entities.size();

	for (int i = 0; i < nbIterations; i++)
	{
		entity->Update();

		//When the entity has finished its update, increment the counter to
		//inform it has finished.
		//To avoid concurrent access, the next block is locked.

		std::unique_lock<std::mutex> lock_cv(m_mtx);
		m_countFinishedUpdate++;
		//ConsoleUtilsThreadSafe::Instance().PrintThreadSafe(" Increment counter : ", m_countFinishedUpdate);

		//If all entities have finished their update loop
		if (m_countFinishedUpdate >= nbThreads)
		{
			//reset the counter
			m_countFinishedUpdate = 0;

			//Global event that must happen once per Update Loop after all Updates
			MessageDispatcher::Instance()->DispatchDelayedMessages();

			//Sleep(100);

			//unlock all threads
			ConsoleUtilsThreadSafe::Instance().PrintThreadSafe(" Notify All! #", (i + 1));
			m_cv.notify_all(); 
			
		}
		else 
		{
			//wait for the last thread to finish
			//ConsoleUtilsThreadSafe::Instance().PrintThreadSafe(" Wait for Notify");
			m_cv.wait(lock_cv); //the lock is automatically released here
		}
	}
}

/*
template <typename ... T>
void MultithreadManager::PrintThreadSafe(T&& ... args)
{
	std::lock_guard<std::mutex> lock(m_mtx_cmd);
	(std::cout << ... << std::forward<T>(args)) << std::endl;
} */

void MultithreadManager::RunMultithreadAgents(int nbIterations)
{
	//Make and run a thread for all entities.

	std::vector<std::thread> threads;

	m_countFinishedUpdate = 0;

	for (auto& entity : m_entities)
	{
		//Start an entity on its own thread
		threads.emplace_back([&entity, &nbIterations, this]() 
		{
			StartThread(entity, nbIterations);
		});
	}

	//All agents started, we wait until they are all done.
	for (auto& const thread : threads)
	{
		thread.join();
	}


}

void MultithreadManager::RegisterEntity(BaseGameEntity* entity)
{
	m_entities.push_back(entity);
}
