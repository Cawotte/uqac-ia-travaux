#include "Raven_Team.h"
#include "Raven_Bot.h"
#include "Raven_TeamArea.h"
#include "misc/Cgdi.h"

#include <algorithm>

//init static
int Raven_Team::teamCount = 0;

void Raven_Team::GetTeamColor(int teamID)
{
	//Brush is used to fill colors
	//Pen is used to draw lines

	switch (teamID)
	{
	case 0:
		gdi->BlueBrush();
		gdi->BluePen();
		break;
	case 1:
		gdi->YellowBrush();
		gdi->YellowPen();
		break;
	case 2:
		gdi->GreenBrush();
		gdi->GreenPen();
		break;
	case 3:
		gdi->OrangeBrush();
		gdi->OrangePen();
		break;
	case 4:
		gdi->RedBrush();
		gdi->RedPen();
		break;
	default:
		gdi->BrownBrush();
		gdi->BrownPen();
		break;
	}
}

Raven_Team::Raven_Team(Raven_Bot* leader) : 
	m_pTeamLeader(leader),
	m_pTarget(NULL)
{
	//The leader also belong to the team
	AddToTeam(leader);

	m_teamID = teamCount;
	teamCount++;
}

Raven_Team::~Raven_Team()
{
	//Remove all members from that team
	for (const auto member : m_vecTeamMembers)
	{
		member->SetTeam(NULL);
	}

}

bool Raven_Team::IsInTeam(Raven_Bot* const bot) const
{
	for (const auto member : m_vecTeamMembers)
	{
		if (member->ID() == bot->ID())
		{
			return true;
		}
	}

	return false;
}

void Raven_Team::AddToTeam(Raven_Bot* const bot)
{
	if (!IsInTeam(bot))
	{
		m_vecTeamMembers.push_back(bot);
		bot->SetTeam(this);
	}
}

void Raven_Team::RemoveFromTeam(Raven_Bot* const bot)
{
	if (IsInTeam(bot))
	{
		m_vecTeamMembers.erase(std::remove(m_vecTeamMembers.begin(), m_vecTeamMembers.end(), bot));
		bot->SetTeam(NULL);
	}

}

void Raven_Team::UseTeamColor()
{
	GetTeamColor(m_teamID);
}
