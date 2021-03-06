#include "MultithreadManager.h"

#include "misc/ConsoleUtils.h" //Sleep
#include "MessageDispatcher.h"

//print thread-safe
#include "ConsoleUtilsThreadSafe.h"

void MultithreadManager::StartThread(BaseGameEntity* entity, const int nbIterations, const int sleepTime)
{

	for (int i = 0; i < nbIterations; i++)
	{
		entity->Update();

		//When the entity has finished its update, increment the counter to
		//inform it has finished.
		//To avoid concurrent access, the next block is thread-safe locked.

		std::unique_lock<std::mutex> lock_cv(m_mtx);
		m_countFinishedUpdate++;

		//If all entities have finished their update loop
		if (m_countFinishedUpdate >= m_entities.size())
		{
			//reset the counter
			m_countFinishedUpdate = 0;

			//Global event that must happen once per Update Loop after all Updates
			MessageDispatcher::Instance()->DispatchDelayedMessages();

			if (sleepTime > 0)
			{
				Sleep(sleepTime);
			}

			//unlock all threads
			//CoutSafe.PrintThreadSafe("Loop #", i + 1);
			m_cv.notify_all(); 
			
		}
		else 
		{
			//wait for the last thread to finish

			m_cv.wait(lock_cv); //the lock is automatically released here
		}
	}
}

void MultithreadManager::RunAllEntitiesOnThreads(const int nbIterations, const int sleepTime)
{
	//Make and run a thread for all entities.

	std::vector<std::thread> threads;

	m_countFinishedUpdate = 0;

	for (auto& entity : m_entities)
	{
		//Start an entity on its own thread
		threads.emplace_back([&entity, &nbIterations, &sleepTime, this]() 
		{
			StartThread(entity, nbIterations, sleepTime);
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
