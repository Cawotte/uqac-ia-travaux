#ifndef LEARNING_BOT_H
#define LEARNING_BOT_H

#pragma warning (disable:4786)
#include "Raven_Bot.h"
#include "Raven_Game.h"
#include "CData.h"
#include "CNeuralNet.h"
#include <chrono>


class LearningBot :	public Raven_Bot
{
private:
	CNeuralNet m_ModeleAppris;

public:

	std::chrono::steady_clock::time_point begin;
	LearningBot(Raven_Game* world, Vector2D pos);
	~LearningBot();

	void SetDead() ;
	void SetAlive();



	void Update();
	

};

#endif

