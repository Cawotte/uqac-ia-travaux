#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Alcoholic.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

//Multithreading
#include "AgentThread.h"
#include "thread"
#include <mutex>
#include <condition_variable>

std::ofstream os;

int main()
{
	//define this to send output to a text file (see locations.h)
	#ifdef TEXTOUTPUT
		os.open("output.txt");
	#endif

	//seed random number generator
	srand((unsigned) time(NULL));

	// ----- INITIALIZE AGENTS

	//create a miner
	std::unique_ptr<Miner> bob = std::make_unique<Miner>(ent_Miner_Bob);

	//create his wife
	std::unique_ptr<MinersWife> elsa = std::make_unique<MinersWife>(ent_Elsa);

	//create his arch-nemesis
	std::unique_ptr<Alcoholic> alcoholic = std::make_unique<Alcoholic>(ent_Alcoholic); 


	//register them with the entity manager
	EntityMgr->RegisterEntity(bob.get());
	EntityMgr->RegisterEntity(elsa.get());
	EntityMgr->RegisterEntity(alcoholic.get());


	// --------- Multithreading

	//locks and condition variables
	std::mutex mtx;
	std::condition_variable cv;

	
	std::thread bobThread(AgentThread(), bob.get(), &mtx, &cv);
	std::thread elsaThread(AgentThread(), elsa.get(), &mtx, &cv);
	std::thread alcoThread(AgentThread(), alcoholic.get(), &mtx, &cv);
	
	//The agents will be run in the thread, we keep them synchronized here.
	for (int i=0; i<30; ++i)
	{ 

		//dispatch any delayed messages
		Dispatch->DispatchDelayedMessages();

		Sleep(50);
		cv.notify_all();
	} 
	

	//smart ptr do the cleaning on its own.

	//wait for a keypress before exiting
	PressAnyKeyToContinue();


	return 0;
}






