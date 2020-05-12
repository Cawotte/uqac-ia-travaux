#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

WifesGlobalState* WifesGlobalState::Instance()
{
  static WifesGlobalState instance;

  return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife)
{
  //1 in 10 chance of needing the bathroom (provided she is not already
  //in the bathroom)
  if ( (RandFloat() < 0.1) && 
       !wife->GetFSM()->isInState(*VisitBathroom::Instance()) )
  {
    wife->GetFSM()->ChangeState(VisitBathroom::Instance());
  }
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Telegram& msg)
{

  switch(msg.Msg)
  {
  case Msg_HiHoneyImHome:
   {
        Dispatch->PrintSafeHandleConfirmation(wife);

        wife->PrintThreadSafe(": Hi honey. Let me make you some of mah fine country stew");

        wife->GetFSM()->ChangeState(CookStew::Instance());
   }

   return true;

  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
  static DoHouseWork instance;

  return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
    wife->PrintThreadSafe(": Time to do some more housework!");
}


void DoHouseWork::Execute(MinersWife* wife)
{
  switch(RandInt(0,2))
  {
  case 0:

      wife->PrintThreadSafe(": Moppin' the floor");

    break;

  case 1:

      wife->PrintThreadSafe(": Washin' the dishes");

    break;

  case 2:

      wife->PrintThreadSafe(": Makin' the bed");

    break;
  }
}

void DoHouseWork::Exit(MinersWife* wife)
{
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{
    wife->PrintThreadSafe(": Walkin' to the can. Need to powda mah pretty li'lle nose");
}


void VisitBathroom::Execute(MinersWife* wife)
{
    wife->PrintThreadSafe(": Ahhhhhh! Sweet relief!");

    wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife)
{
    wife->PrintThreadSafe(": Leavin' the Jon");
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
  static CookStew instance;

  return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
  //if not already cooking put the stew in the oven
  if (!wife->Cooking())
  {
    wife->PrintThreadSafe(": Putting the stew in the oven");
    //cout << "\n" << GetNameOfEntity(wife->ID()) << ": Putting the stew in the oven";
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    Dispatch->DispatchMessage(1.5,                  //time delay
                              wife->ID(),           //sender ID
                              wife->ID(),           //receiver ID
                              Msg_StewReady,        //msg
                              NO_ADDITIONAL_INFO); 

    wife->SetCooking(true);
  }
}


void CookStew::Execute(MinersWife* wife)
{
    wife->PrintThreadSafe(": Fussin' over food");
  //cout << "\n" << GetNameOfEntity(wife->ID()) << ": Fussin' over food";
}

void CookStew::Exit(MinersWife* wife)
{
  //SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

    wife->PrintThreadSafe(": Puttin' the stew on the table");
  //cout << "\n" << GetNameOfEntity(wife->ID()) << ": Puttin' the stew on the table";
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_StewReady:
    {
      //cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
      //     " at time: " << Clock->GetCurrentTime();

        Dispatch->PrintSafeHandleConfirmation(wife);
      /*CoutSafe.PrintThreadSafe(
          ": Message received by ",
          GetNameOfEntity(wife->ID()),
          "at time :",
          Clock->GetCurrentTime(),
          BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);*/
      wife->PrintThreadSafe(": StewReady!Lets eat");
     // SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      //cout << "\n" << GetNameOfEntity(wife->ID()) << ": StewReady! Lets eat";

      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                wife->ID(),
                                ent_Miner_Bob,
                                Msg_StewReady,
                                NO_ADDITIONAL_INFO);

      wife->SetCooking(false);

      wife->GetFSM()->ChangeState(DoHouseWork::Instance());               
    }

    return true;

  }//end switch

  return false;
}