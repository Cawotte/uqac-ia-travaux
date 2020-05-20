#include "Alcoholic.h"
#include "misc/ConsoleUtils.h"

bool Alcoholic::HandleMessage(const Telegram& msg)
{
    return m_pStateMachine->HandleMessage(msg);
}


void Alcoholic::Update()
{

    m_pStateMachine->Update();
}