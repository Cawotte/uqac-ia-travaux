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

// ----- VARIABLES  -------
bool		const USE_MULTITHREADING	= true;
bool        const ASK_STARTING_STATE    = true;
int			const NB_ITERATIONS			= 30;
int			const UPDATE_SLEEP_TIME		= 800;


void askInitialState(Miner* bob, MinersWife* elsa, Alcoholic* alcoholic);

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

    if (ASK_STARTING_STATE)
    {
        askInitialState(bob.get(), elsa.get(), alcoholic.get());
    }

	//register them with the entity manager
	EntityMgr->RegisterEntity(bob.get());
	EntityMgr->RegisterEntity(elsa.get());
	EntityMgr->RegisterEntity(alcoholic.get());

	if (USE_MULTITHREADING)
	{

        std::cout << "\nExecution IS multithreaded." << std::endl;
		// --------- Multithreading
		MultithreadManager multithreadManager;

		multithreadManager.RegisterEntity(bob.get());
		multithreadManager.RegisterEntity(elsa.get());
		multithreadManager.RegisterEntity(alcoholic.get());

		//Run threads and wait until they are all finished
		multithreadManager.RunAllEntitiesOnThreads(NB_ITERATIONS, UPDATE_SLEEP_TIME);
	}
	else
	{

        std::cout << "\nExecution is NOT multithreaded." << std::endl;
		for (int i = 0; i < NB_ITERATIONS; ++i)
		{
			bob->Update();
			elsa->Update();
			alcoholic->Update();

			//dispatch any delayed messages
			Dispatch->DispatchDelayedMessages();

			//CoutSafe.PrintThreadSafe("Loop #", i + 1);

			if (UPDATE_SLEEP_TIME > 0)
			{
				Sleep(UPDATE_SLEEP_TIME);
			}
		}
	}

	
	//smart ptr do the cleaning on its own.

	//wait for a keypress before exiting
	PressAnyKeyToContinue();


	return 0;
}

void askInitialState(Miner* bob, MinersWife* elsa, Alcoholic* alcoholic)
{
    int bobState = 0;
    printf("\nPlease choose Bob's initial State : \n1. GoHomeAndSleepTilRested (default)   \n2. EnterMineAndDigForNugget    \n3. VisitBankAndDepositGold   \n4. QuenchThirst \n5. EatStew \n\n Choice : ");
    scanf_s("%i", &bobState);

    int elsaState = 0;

    printf("\nPlease choose Elsa's initial State : \n1. DoHouseWork (default)   \n2. VisitBathroom   \n3. CookStew  \n\n Choice : ");
    scanf_s("%i", &elsaState);

    int alcoholicState = 0;
    printf("\nPlease choose Alcholic's initial State : \n1. DrinkBeer (default)   \n2. Drunk \n\n Choice : ");
    scanf_s("%i", &alcoholicState);



    switch (bobState)
    {
    case 1:
        bob->GetFSM()->SetCurrentState(GoHomeAndSleepTilRested::Instance());
        break;

    case 2:
        bob->GetFSM()->SetCurrentState(EnterMineAndDigForNugget::Instance());
        break;

    case 3:
        bob->GetFSM()->SetCurrentState(VisitBankAndDepositGold::Instance());
        break;
    case 4:
        bob->GetFSM()->SetCurrentState(QuenchThirst::Instance());
        break;
    case 5:
        bob->GetFSM()->SetCurrentState(EatStew::Instance());
        break;
    default:
        bob->GetFSM()->SetCurrentState(GoHomeAndSleepTilRested::Instance());
        break;
    }

    switch (elsaState)
    {
    case 1:
        elsa->GetFSM()->SetCurrentState(DoHouseWork::Instance());
        break;
    case 2:
        elsa->GetFSM()->SetCurrentState(VisitBathroom::Instance());

    default:
        elsa->GetFSM()->SetCurrentState(CookStew::Instance());
        break;
    }

    switch (alcoholicState)
    {
    case 1:
        alcoholic->GetFSM()->SetCurrentState(DrinkBeer::Instance());
        break;
    case 2:
        alcoholic->GetFSM()->SetCurrentState(Drunk::Instance());
        break;
    default:
        alcoholic->GetFSM()->SetCurrentState(DrinkBeer::Instance());
        break;
    }


}






