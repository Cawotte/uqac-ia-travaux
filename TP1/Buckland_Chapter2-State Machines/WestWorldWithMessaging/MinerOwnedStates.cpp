#include "MinerOwnedStates.h"
#include "fsm/State.h"
#include "Miner.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
  //if the miner is not already located at the goldmine, he must
  //change location to the gold mine
    if (pMiner->Location() != goldmine)
    {
        pMiner->PrintThreadSafe(": Walkin' to the goldmine");

        pMiner->ChangeLocation(goldmine);
    }
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{  
  //Now the miner is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  pMiner->PrintThreadSafe(": Pickin' up a nugget");

  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull())
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pMiner->Thirsty())
  {
    pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
    pMiner->PrintThreadSafe(": Ah'm leavin' the goldmine with mah pockets full o' sweet gold");
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {
      pMiner->PrintThreadSafe(": Goin' to the bank. Yes siree");

    pMiner->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);

  pMiner->PrintThreadSafe(
      ": Depositing gold. Total savings now: ",
      pMiner->Wealth());

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
      pMiner->PrintThreadSafe(": WooHoo! Rich enough for now. Back home to mah li'lle lady");
      
        pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      
  }

  //otherwise get more gold
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
    pMiner->PrintThreadSafe(": Leavin' the bank");
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
  if (pMiner->Location() != shack)
  {
      pMiner->PrintThreadSafe(": Walkin' home");

    pMiner->ChangeLocation(shack); 

    //let the wife know I'm home
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->ID(),        //ID of sender
                              ent_Elsa,            //ID of recipient
                              Msg_HiHoneyImHome,   //the message
                              NO_ADDITIONAL_INFO);    
  }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{ 
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued())
  {
      pMiner->PrintThreadSafe(": All mah fatigue has drained away. Time to find more gold");

     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else 
  {
    //sleep
    pMiner->DecreaseFatigue();

    pMiner->PrintThreadSafe(": ZZZZ... ");
  } 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{ 
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
   //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady:

        Dispatch->PrintSafeHandleConfirmation(pMiner);

        pMiner->PrintThreadSafe(": Okay Hun, ahm a comin'!");

        pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
        return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon);

    pMiner->PrintThreadSafe(": Boy, ah sure is thirsty! Walking to the saloon");

    //let the alcoholic know I'm in the saloon
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
        pMiner->ID(),        //ID of sender
        ent_Alcoholic,       //ID of recipient
        Msg_ImInTheSaloon,   //the message
        NO_ADDITIONAL_INFO);
  }
}

void QuenchThirst::Execute(Miner* pMiner)
{
  pMiner->BuyAndDrinkAWhiskey();

  pMiner->PrintThreadSafe(": That's mighty fine sippin' liquer");

  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void QuenchThirst::Exit(Miner* pMiner)
{ 
  //The miner doesn't leave the saloon if it goes into a fight, making that message wrong
  //cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the saloon, feelin' good";
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
    //If the alcoholic picked up a fight, fight!

    switch (msg.Msg)
    {
    case Msg_StartingAFight:

        Dispatch->PrintSafeHandleConfirmation(pMiner);

        pMiner->PrintThreadSafe(": You're messing' with the wrong dude, alcoholic");

        pMiner->GetFSM()->ChangeState(FightAlcoholic::Instance());

        return true;

    }

    return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
    pMiner->PrintThreadSafe(": Smells Reaaal goood Elsa!");
}

void EatStew::Execute(Miner* pMiner)
{
    pMiner->PrintThreadSafe(": Tastes real good too!");

  pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{
    pMiner->PrintThreadSafe(": Thankya li'lle lady. Ah better get back to whatever ah wuz doin'");
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


// -------------- Methods for FightAlcoholic State --------------

FightAlcoholic* FightAlcoholic::Instance()
{
    static FightAlcoholic instance;

    return &instance;
}

void FightAlcoholic::Enter(Miner* miner)
{
    miner->PrintThreadSafe(": You're gonna regret that!");
}

void FightAlcoholic::Execute(Miner* miner)
{
    miner->PrintThreadSafe(": Hope ya' learned your lesson!");

    miner->GetFSM()->RevertToPreviousState();
}

void FightAlcoholic::Exit(Miner* miner)
{
    miner->PrintThreadSafe(": Don't cross my path again");
}

bool FightAlcoholic::OnMessage(Miner* agent, const Telegram& msg)
{
    return false;
}
