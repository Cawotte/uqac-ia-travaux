#include "Alcoholic.h"
#include "misc/ConsoleUtils.h"

bool Alcoholic::HandleMessage(const Telegram& msg)
{
    return m_pStateMachine->HandleMessage(msg);
}


void Alcoholic::Update()
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    m_pStateMachine->Update();
}