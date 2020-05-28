#include "Leader.h"

#include "SteeringBehaviors.h"
#include "ParamLoader.h"
#include <misc\Cgdi.h>

Leader::Leader(GameWorld* world, 
				Vector2D position, 
				double rotation, 
				Vector2D velocity,
				bool isPlayerControlled) : Vehicle(world,
											position,
											rotation,
											velocity,           //velocity
											Prm.VehicleMass,          //mass
											Prm.MaxSteeringForce,     //max force
											Prm.MaxSpeed * 0.75f,             //max velocity
											Prm.MaxTurnRatePerSecond, //max turn rate
											Prm.VehicleScale * 3.f),
											m_bIsPlayerControlled(isPlayerControlled)
{

	Steering()->FlockingOff();

	if (m_bIsPlayerControlled)
	{
		//Follow player's crosshair
		Steering()->ArriveOn();
	}
	else
	{
		//Wander on its own
		Steering()->WanderOn();
	}
}

void Leader::SetIsPlayerControlled(bool isPlayerControlled)
{

	m_bIsPlayerControlled = isPlayerControlled;

	if (m_bIsPlayerControlled)
	{
		//Disable wandering and enable player control
		Steering()->WanderOff();
		Steering()->ArriveOn();
	}
	else
	{
		//Disable player control and enable wandering
		Steering()->ArriveOff();
		Steering()->WanderOn();
	}

}

void Leader::UseDefaultColor()
{
	gdi->RedPen();
}
