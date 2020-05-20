#ifndef MULTITHREAD_MANAGER_H
#define MULTITHREAD_MANAGER_H

//------------------------------------------------------------------------
//
//  Name:   MultithreadManager.h
//
//  Desc:   A class handling running BaseGameEntity concurrently on
//			several threads.
//
//------------------------------------------------------------------------

#include "BaseGameEntity.h"
#include <vector>

#include <mutex>

class MultithreadManager
{

private:

	std::vector<BaseGameEntity*> m_entities;

	std::mutex m_mtx;
	//std::mutex m_mtx_cmd;

	std::condition_variable m_cv;


	//Number of threads that have finished the current Update loop
	int m_countFinishedUpdate;

	// --- METHODS ---

	//Start a separate thread on which to run entity's update for nbIter loops.
	void StartThread(BaseGameEntity* entity, const int nbIterations, const int sleepTime);

public:

	//Start a separate thread for each registered entities, and manage them.
	//Block the execution until they are all finished.
	void RunAllEntitiesOnThreads(const int nbIterations, const int sleepTime);

	//Add an entity that will be run on its own thread.
	void RegisterEntity(BaseGameEntity* entity);

};

#endif

