#include "Raven_Feature.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "HideGoal_Evaluator.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"






//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double HideGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
    double Desirability = 0.0;

    //Check if there's no health item in current world
        if (Raven_Feature::DistanceToItem(pBot, type_health) == 1) 
        {
            const double Tweaker = 1.0;
            Desirability = Tweaker * (1 - Raven_Feature::Health(pBot));
        }



        //bias the value according to the personality of the bot
        //Desirability *= m_dCharacterBias;

    return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void HideGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
    pBot->GetBrain()->AddGoal_Hide();
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void HideGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
    gdi->TextAtPos(Position, "HIIIIIIIIIIIDe AT: ");//+ ttos(CalculateDesirability(pBot), 2));
    return;

   // std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
   // gdi->TextAtPos(Position + Vector2D(0, 12), s);
}
