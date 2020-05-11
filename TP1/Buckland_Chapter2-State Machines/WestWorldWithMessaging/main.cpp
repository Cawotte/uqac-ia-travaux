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
#include "MultithreadManager.h"

std::ofstream os;

bool const USE_MULTITHREADING = true;
int const NB_ITERATIONS = 30;

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

	if (USE_MULTITHREADING)
	{

		// --------- Multithreading
		MultithreadManager multithreadManager;

		multithreadManager.RegisterEntity(bob.get());
		multithreadManager.RegisterEntity(elsa.get());
		multithreadManager.RegisterEntity(alcoholic.get());

		multithreadManager.RunMultithreadAgents(NB_ITERATIONS);
	}
	else
	{

		//The agents will be run in the thread, we keep them synchronized here.
		for (int i = 0; i < NB_ITERATIONS; ++i)
		{
			bob->Update();
			elsa->Update();
			alcoholic->Update();

			//dispatch any delayed messages
			Dispatch->DispatchDelayedMessages();

			Sleep(500);
		}
	}

	
	//smart ptr do the cleaning on its own.

	//wait for a keypress before exiting
	PressAnyKeyToContinue();


	return 0;
}






