#ifndef LEADER_H
#define LEADER_H

#include "Vehicle.h"

class Leader : public Vehicle
{

public:

	Leader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity);

};

#endif

