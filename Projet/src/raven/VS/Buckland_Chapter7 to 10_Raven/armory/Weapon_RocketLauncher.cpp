#include "Weapon_RocketLauncher.h"
#include "../Raven_Bot.h"
#include "misc/Cgdi.h"
#include "../Raven_Game.h"
#include "../Raven_Map.h"
#include "../lua/Raven_Scriptor.h"
#include "fuzzy/FuzzyOperators.h"


//--------------------------- ctor --------------------------------------------
//-----------------------------------------------------------------------------
RocketLauncher::RocketLauncher(Raven_Bot* owner) :

	Raven_Weapon(type_rocket_launcher,
		script->GetInt("RocketLauncher_DefaultRounds"),
		script->GetInt("RocketLauncher_MaxRoundsCarried"),
		script->GetDouble("RocketLauncher_FiringFreq"),
		script->GetDouble("RocketLauncher_IdealRange"),
		script->GetDouble("Rocket_MaxSpeed"),
		owner)
{
	//setup the vertex buffer
	const int NumWeaponVerts = 8;
	const Vector2D weapon[NumWeaponVerts] = { Vector2D(0, -3),
											 Vector2D(6, -3),
											 Vector2D(6, -1),
											 Vector2D(15, -1),
											 Vector2D(15, 1),
											 Vector2D(6, 1),
											 Vector2D(6, 3),
											 Vector2D(0, 3)
	};
	for (int vtx = 0; vtx < NumWeaponVerts; ++vtx)
	{
		m_vecWeaponVB.push_back(weapon[vtx]);
	}

	//setup the fuzzy module
	InitializeFuzzyModule();

}


//------------------------------ ShootAt --------------------------------------
//-----------------------------------------------------------------------------
inline void RocketLauncher::ShootAt(Vector2D pos)
{
	if (NumRoundsRemaining() > 0 && isReadyForNextShot())
	{
		//fire off a rocket!
		m_pOwner->GetWorld()->AddRocket(m_pOwner, pos);

		m_iNumRoundsLeft--;

		UpdateTimeWeaponIsNextAvailable();

		//add a trigger to the game so that the other bots can hear this shot
		//(provided they are within range)
		m_pOwner->GetWorld()->GetMap()->AddSoundTrigger(m_pOwner, script->GetDouble("RocketLauncher_SoundRange"));
	}
}

//---------------------------- Desirability -----------------------------------
//
//-----------------------------------------------------------------------------
double RocketLauncher::GetDesirability(double DistToTarget)
{
	if (m_iNumRoundsLeft == 0)
	{
		m_dLastDesirabilityScore = 0;
	}
	else
	{

		//fuzzify distance and amount of ammo
		m_FuzzyModule.Fuzzify("DistToTarget", DistToTarget);
		m_FuzzyModule.Fuzzify("AmmoStatus", (double)m_iNumRoundsLeft);
		m_FuzzyModule.Fuzzify("RemainingHealth", (double)m_pOwner->Health());
		m_FuzzyModule.Fuzzify("CooldownLeft", GetCooldownLeft());

		m_dLastDesirabilityScore = m_FuzzyModule.DeFuzzify("Desirability", FuzzyModule::max_av);
	}

	return m_dLastDesirabilityScore;
}

//-------------------------  InitializeFuzzyModule ----------------------------
//
//  set up some fuzzy variables and rules
//-----------------------------------------------------------------------------
void RocketLauncher::InitializeFuzzyModule()
{
	FuzzyVariable& DistToTarget = m_FuzzyModule.CreateFLV("DistToTarget");

	FzSet& Target_Close = DistToTarget.AddLeftShoulderSet("Target_Close", 0, 25, 90);
	FzSet& Target_MedClose = DistToTarget.AddTriangularSet("Target_MedClose", 20, 90, 150);
	FzSet& Target_Medium = DistToTarget.AddTriangularSet("Target_Medium", 25, 150, 300);
	FzSet& Target_MedFar = DistToTarget.AddTriangularSet("Target_MedFar", 150, 225, 300);
	FzSet& Target_Far = DistToTarget.AddRightShoulderSet("Target_Far", 150, 300, 1000);

	FuzzyVariable& Desirability = m_FuzzyModule.CreateFLV("Desirability");
	FzSet& VeryDesirable = Desirability.AddRightShoulderSet("VeryDesirable", 70, 90, 100);
	FzSet& QuiteDesirable = Desirability.AddTriangularSet("QuiteDesirable", 45, 60, 80);
	FzSet& Desirable = Desirability.AddTriangularSet("Desirable", 30, 45, 60);
	FzSet& NotMuchDesirable = Desirability.AddTriangularSet("NotMuchDesirable", 15, 30, 45);
	FzSet& Undesirable = Desirability.AddLeftShoulderSet("Undesirable", 0, 15, 30);

	FuzzyVariable& AmmoStatus = m_FuzzyModule.CreateFLV("AmmoStatus");
	FzSet& Ammo_Loads = AmmoStatus.AddRightShoulderSet("Ammo_Loads", 45, 50, 100);
	FzSet& Ammo_Many = AmmoStatus.AddTriangularSet("Ammo_Many", 35, 50, 60);
	FzSet& Ammo_Okay = AmmoStatus.AddTriangularSet("Ammo_Okay", 10, 30, 40);
	FzSet& Ammo_Enough = AmmoStatus.AddTriangularSet("Ammo_Enough", 5, 10, 20);
	FzSet& Ammo_Low = AmmoStatus.AddTriangularSet("Ammo_Low", 0, 0, 5);

	//Use Health as a rule
	int halfHealth = m_pOwner->MaxHealth() / 2;
	int quarterHealth = m_pOwner->MaxHealth() / 4;

	FuzzyVariable& RemainingHealth = m_FuzzyModule.CreateFLV("RemainingHealth");
	FzSet& High_Health = RemainingHealth.AddRightShoulderSet("High_Health", halfHealth, halfHealth + quarterHealth, m_pOwner->MaxHealth());
	FzSet& Medium_Health = RemainingHealth.AddTriangularSet("Medium_Health", halfHealth - quarterHealth, halfHealth, halfHealth + quarterHealth);
	FzSet& Low_Health = RemainingHealth.AddLeftShoulderSet("Low_Health", 0, quarterHealth, halfHealth);

	//Time left for the weapon to be available

	//RocketLauncher_FiringFreq = 1.5
	FuzzyVariable& CooldownLeft = m_FuzzyModule.CreateFLV("CooldownLeft");

	FzSet& High_Cooldown = CooldownLeft.AddLeftShoulderSet("High_Cooldown", 0.9, 1.25, 1.5);
	FzSet& Medium_Cooldown = CooldownLeft.AddTriangularSet("Medium_Cooldown", 0.4, 0.7, 1);
	FzSet& Low_Cooldown = CooldownLeft.AddRightShoulderSet("Low_Cooldown", 0, 0.25, 0.5);


	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Loads), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Many), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Okay), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Enough), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Low), Undesirable);

	m_FuzzyModule.AddRule(FzAND(Target_MedClose, Ammo_Loads), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedClose, Ammo_Many), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedClose, Ammo_Okay), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedClose, Ammo_Enough), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedClose, Ammo_Low), Undesirable);

	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Loads), VeryDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Many), QuiteDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Okay), Desirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Enough), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Low), Desirable);

	m_FuzzyModule.AddRule(FzAND(Target_MedFar, Ammo_Loads), QuiteDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedFar, Ammo_Many), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedFar, Ammo_Okay), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedFar, Ammo_Enough), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_MedFar, Ammo_Low), Undesirable);

	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Loads), Desirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Many), NotMuchDesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Okay), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Enough), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Low), Undesirable);

	//New rules
	m_FuzzyModule.AddRule(FzAND(Low_Health, Target_Close), Undesirable);
	m_FuzzyModule.AddRule(FzAND(Low_Health, Target_Medium), Desirable);
	m_FuzzyModule.AddRule(FzAND(Low_Health, Target_Far), Desirable);

	m_FuzzyModule.AddRule(FzAND(High_Health, Target_Close), Desirable);
	m_FuzzyModule.AddRule(FzAND(High_Health, Target_Medium), VeryDesirable);
	m_FuzzyModule.AddRule(FzAND(High_Health, Target_Far), Desirable);

	m_FuzzyModule.AddRule(FzAND(Low_Cooldown, Target_Close), Desirable);
	m_FuzzyModule.AddRule(FzAND(Low_Cooldown, Target_Medium), VeryDesirable);
	m_FuzzyModule.AddRule(FzAND(Low_Cooldown, Target_Far), Desirable);

	m_FuzzyModule.AddRule(FzAND(High_Cooldown, Target_Close), Undesirable);
	m_FuzzyModule.AddRule(FzAND(High_Cooldown, Target_Medium), Undesirable);
	m_FuzzyModule.AddRule(FzAND(High_Cooldown, Target_Far), Undesirable);



}


//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void RocketLauncher::Render()
{
	m_vecWeaponVBTrans = WorldTransform(m_vecWeaponVB,
		m_pOwner->Pos(),
		m_pOwner->Facing(),
		m_pOwner->Facing().Perp(),
		m_pOwner->Scale());

	gdi->RedPen();

	gdi->ClosedShape(m_vecWeaponVBTrans);
}