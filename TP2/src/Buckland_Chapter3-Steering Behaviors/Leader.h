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

	//To set if the Leader wander or is controlled by the player's cursor
	void SetIsPlayerControlled(bool isPlayerControlled);

	bool IsPlayerControlled() { return m_bIsPlayerControlled; }

	//Color to draw the agent with
	void UseDefaultColor() override;
};

#endif

