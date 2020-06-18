#include "Goal_Hide.h"
#include "../Raven_Bot.h"
#include "../Raven_SteeringBehaviors.h"
#include "../Raven_Game.h"

#include "Messaging/Telegram.h"
#include "../Raven_Messages.h"
#include "Raven_Feature.h"

#include "debug/DebugConsole.h"
#include "misc/cgdi.H"


//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Hide::Activate()
{
    debug_con << "ACTIVATE HIDE";

    m_iStatus = active;
    double distance = Raven_Feature::DistanceToItem(m_pOwner, type_bot);
    if (distance < 1) 
    {
        debug_con << "FLEEE";
        m_pOwner->GetSteering()->FleeOn();
    }
}



//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_Hide::Process()
{
    //if status is inactive, call Activate()
    ActivateIfInactive();

    //if target goes in field of view terminate
    if (Raven_Feature::DistanceToItem(m_pOwner, type_health)<1)
    {
        m_iStatus = inactive;
    }

    //else if bot reaches the target position set status to inactive so the goal 
    //is reactivated on the next update-step


    return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Hide::Terminate()
{
    debug_con << "TERMINATE HIDE";

    m_pOwner->GetSteering()->FleeOff();
}

//---------------------------- Render -----------------------------------------

void Goal_Hide::Render()
{
    //#define SHOW_TARGET
#ifdef SHOW_TARGET
    gdi->OrangePen();
    gdi->HollowBrush();

    gdi->Line(m_pOwner->Pos(), m_vStrafeTarget);
    gdi->Circle(m_vStrafeTarget, 3);
#endif

}
