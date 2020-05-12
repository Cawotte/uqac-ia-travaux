#ifndef ALCOHOLIC_H
#define ALCOHOLIC_H


//------------------------------------------------------------------------
//
//  Name:   Alcoholic.h
//
//  Desc:   A class defining an alcoholic that will occasionally fight
//			with the miner
//
//------------------------------------------------------------------------

#include "BaseGameEntity.h"
#include "Locations.h"
#include "fsm/StateMachine.h"
#include "AlcoholicOwnedStates.h"


template <class entity_type> class State;
struct Telegram;

//Above this value the alcoholic is drunk
const int DrunkLevel = 4;

class Alcoholic : public BaseGameEntity
{

private:

    //No need for delete ptr with unique_ptr
    typedef std::unique_ptr<StateMachine<Alcoholic>> StateMachineAlcoholic;

    //an instance of the state machine class
    StateMachineAlcoholic m_pStateMachine;

    location_type         m_Location;


    //the higher the value, the drunker the alcoholic
    int                   m_iDrunkeness;

public:

    Alcoholic(int id) :
        m_Location(saloon),
        m_iDrunkeness(0),
        BaseGameEntity(id)
    {
        //set up state machine
        m_pStateMachine = std::make_unique<StateMachine<Alcoholic>>(this);

        m_pStateMachine->SetCurrentState(DrinkBeer::Instance());
    }

    void Update();

    virtual bool  HandleMessage(const Telegram& msg);


    //Text color for wife
    WORD          TextColor() const override { return FOREGROUND_BLUE | FOREGROUND_INTENSITY; };

    //-------------------------------------------------------------accessors

    
    StateMachine<Alcoholic>* GetFSM() const { 
        return m_pStateMachine.get(); //return raw ptr to not alter ownership
    }

    location_type Location()const { return m_Location; }

    bool    IsDrunk() const { return m_iDrunkeness >= DrunkLevel; }

    void    SoberUp() { m_iDrunkeness = 0; }
    void    DrinkBeer() { m_iDrunkeness += 1; }
};



#endif