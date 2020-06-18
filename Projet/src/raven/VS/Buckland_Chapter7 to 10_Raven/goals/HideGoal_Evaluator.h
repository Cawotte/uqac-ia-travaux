#ifndef RAVEN_HIDE_EVALUATOR
#define RAVEN_HIDE_EVALUATOR
#pragma warning (disable:4786)

//-----------------------------------------------------------------------------
//
//  Name:   HideGoal_Evaluator.h
//
//  Author: Arthur Pardieu - Mehdi Rahmoun - Elie Ensuque - Clémence Petit
//
//  Desc:  class to calculate how desirable the goal of hiding is
//-----------------------------------------------------------------------------

#include "Goal_Evaluator.h"
#include "../Raven_Bot.h"
class HideGoal_Evaluator : public Goal_Evaluator
{
public:
    HideGoal_Evaluator(double bias) :Goal_Evaluator(bias) {}

    double CalculateDesirability(Raven_Bot* pBot);

    void  SetGoal(Raven_Bot* pEnt);

    void RenderInfo(Vector2D Position, Raven_Bot* pBot);
};

#endif