#include "AlcoholicOwnedStates.h"
#include "Alcoholic.h"
#include "EntityNames.h"

#include <iostream>
#include <misc\ConsoleUtils.h>
#include "MessageTypes.h"
#include <Time\CrudeTimer.h>
#include "MessageDispatcher.h"
using std::cout;

// -------------- Methods for DrinkBeer State --------------

DrinkBeer* DrinkBeer::Instance()
{
	static DrinkBeer instance;

	return &instance;
}

void DrinkBeer::Enter(Alcoholic* alcoholic)
{

}

void DrinkBeer::Execute(Alcoholic* alcoholic)
{
	alcoholic->DrinkBeer();

	cout << "\n" << GetNameOfEntity(alcoholic->ID()) << ": " << "Drinkin' a beer";

	if (alcoholic->IsDrunk())
	{
		alcoholic->GetFSM()->ChangeState(Drunk::Instance());
	}
}

void DrinkBeer::Exit(Alcoholic* alcoholic)
{
}

bool DrinkBeer::OnMessage(Alcoholic* agent, const Telegram& msg)
{
	return false;
}



// -------------- Methods for Drunk State --------------


Drunk* Drunk::Instance()
{
	static Drunk instance;

	return &instance;
}

void Drunk::Enter(Alcoholic* alcoholic)
{
	cout << "\n" << GetNameOfEntity(alcoholic->ID()) << ": " << "Hic! Feeling li - Hic! - brawlin' with anyone";
}

void Drunk::Execute(Alcoholic* alcoholic)
{
	cout << "\n" << GetNameOfEntity(alcoholic->ID()) << ": " << "I assuuuuuuuure you.. I'm not dru - Hic! - nk.. hic!";
}

void Drunk::Exit(Alcoholic* alcoholic)
{
}

bool Drunk::OnMessage(Alcoholic* alcoholic, const Telegram& msg)
{
	//If the miner arrived in the saloon, pick up a fight with him.

	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StartingAFight:

		cout << "\nMessage handled by " << GetNameOfEntity(alcoholic->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(alcoholic->ID()) << ": "
			<< "How did ya' dare looking - hic! - at me? I'm gonna break your face!";

		alcoholic->GetFSM()->ChangeState(FightWithTheMiner::Instance());

		return true;

	}

	return false;
}

// -------------- Methods for FightWithMiner State --------------


FightWithTheMiner* FightWithTheMiner::Instance()
{
	static FightWithTheMiner instance;

	return &instance;
}

void FightWithTheMiner::Enter(Alcoholic* alcoholic)
{

	//let the Miner know I'm gonna break his face
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		alcoholic->ID(),        //ID of sender
		ent_Miner_Bob,            //ID of recipient
		Msg_StartingAFight,   //the message
		NO_ADDITIONAL_INFO);
}

void FightWithTheMiner::Execute(Alcoholic* alcoholic)
{
	cout << "\n" << GetNameOfEntity(alcoholic->ID()) << ": " << "Take that! Punchin' ya' right in yer nose!";

	alcoholic->GetFSM()->ChangeState(DrinkBeer::Instance());

}

void FightWithTheMiner::Exit(Alcoholic* alcoholic)
{
	cout << "\n" << GetNameOfEntity(alcoholic->ID()) << ": " << " What is tha' bucket of water for? *Splash* *Splash* Okay, I'm think I'm soberin' up... sorry all";
}

bool FightWithTheMiner::OnMessage(Alcoholic* agent, const Telegram& msg)
{
	return false;
}
