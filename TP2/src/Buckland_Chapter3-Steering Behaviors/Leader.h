#ifndef LEADER_H
#define LEADER_H

#include "Vehicle.h"

class Leader : public Vehicle
{
private:

	bool m_bIsPlayerControlled;

public:

	Leader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		bool isPlayerControlled);

	void SetIsPlayerControlled(bool isPlayerControlled);

	bool IsPlayerControlled() { return m_bIsPlayerControlled; }
};

#endif

