#ifndef PURSUER_H
#define PURSUER_H

#include "Vehicle.h"

class Pursuer : public Vehicle
{

private:

	Vehicle* m_pToPursue;

	Vector2D m_offsetPursuit;

public:

	Pursuer(GameWorld* world, 
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		Vehicle* toPursue,
		Vector2D m_offsetPursuit);
};

#endif

