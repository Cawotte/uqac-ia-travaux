#ifndef ALCHOLIC_OWNED_STATES_H
#define ALCHOLIC_OWNED_STATES_H


//------------------------------------------------------------------------
//
//  Name:   AlcoholicOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Alcoholic class.
//          Note that a global state has not been implemented.
//
//------------------------------------------------------------------------

#include "fsm/State.h"


class Alcoholic;
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the alcoholic will drink beers until he get drunk.
//
//------------------------------------------------------------------------
class DrinkBeer : public State<Alcoholic>
{

private:
	DrinkBeer() {}

    //Private for singleton pattern
    DrinkBeer(const DrinkBeer&);
    DrinkBeer& operator=(const DrinkBeer&);
public:

    //singleton
    static DrinkBeer* Instance();

    virtual void Enter(Alcoholic* alcoholic);

    virtual void Execute(Alcoholic* alcoholic);

    virtual void Exit(Alcoholic* alcoholic);

    virtual bool OnMessage(Alcoholic* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  In this state the alcoholic is drunk, and will pick up a fight
//  with the miner if he comes to the saloon.
//  Once he got into a fight, he'll sober up and restart drinking beer.
//
//------------------------------------------------------------------------
class Drunk : public State<Alcoholic>
{

private:
    Drunk() {}

    //Private for singleton pattern
    Drunk(const Drunk&);
    Drunk& operator=(const Drunk&);
public:

    //singleton
    static Drunk* Instance();

    virtual void Enter(Alcoholic* alcoholic);

    virtual void Execute(Alcoholic* alcoholic);

    virtual void Exit(Alcoholic* alcoholic);

    virtual bool OnMessage(Alcoholic* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  In this state the alcoholic will pick up a fight with the Miner,
//  then have to sober up.
//
//------------------------------------------------------------------------
class FightWithTheMiner : public State<Alcoholic>
{

private:
    FightWithTheMiner() {}

    //Private for singleton pattern
    FightWithTheMiner(const FightWithTheMiner&);
    FightWithTheMiner& operator=(const FightWithTheMiner&);
public:

    //singleton
    static FightWithTheMiner* Instance();

    virtual void Enter(Alcoholic* alcoholic);

    virtual void Execute(Alcoholic* alcoholic);

    virtual void Exit(Alcoholic* alcoholic);

    virtual bool OnMessage(Alcoholic* agent, const Telegram& msg);
};

#endif