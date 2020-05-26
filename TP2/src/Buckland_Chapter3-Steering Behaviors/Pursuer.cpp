#include "Pursuer.h"

#include "SteeringBehaviors.h"
#include "ParamLoader.h"

Pursuer::Pursuer(
	GameWorld* world, 
	Vector2D position,
	double rotation, 
	Vector2D velocity, 
	Vehicle* toPursue) : Vehicle(world,
							position,
							rotation,
							velocity,           //velocity
							Prm.VehicleMass,          //mass
							Prm.MaxSteeringForce * 100.f,     //max force
							Prm.MaxSpeed,             //max velocity
							Prm.MaxTurnRatePerSecond * 100.f, //max turn rate
							Prm.VehicleScale * 1.3f)
{
	Steering()->FlockingOff();
	Steering()->SeparationOn();

	//Offset is relative to pursued agent
	Vector2D offsetBehind(-10.f, 0.0f); //behind agent
	offsetBehind *= 2.f;
	Steering()->OffsetPursuitOn(toPursue, offsetBehind);
}
