#include "Pursuer.h"

#include "SteeringBehaviors.h"
#include "ParamLoader.h"

Pursuer::Pursuer(
	GameWorld* world, 
	Vector2D position,
	double rotation, 
	Vector2D velocity, 
	Vehicle* toPursue,
	Vector2D offsetPursuit) : Vehicle(world,
							position,
							rotation,
							velocity,           //velocity
							Prm.VehicleMass,          //mass
							Prm.MaxSteeringForce,     //max force
							Prm.MaxSpeed,             //max velocity
							Prm.MaxTurnRatePerSecond, //max turn rate
							Prm.VehicleScale * 1.3f),
							m_offsetPursuit(offsetPursuit)
{
	Steering()->FlockingOff();
	Steering()->SeparationOn();

	//Offset is relative to pursued agent
	Steering()->OffsetPursuitOn(toPursue, offsetPursuit);
}
