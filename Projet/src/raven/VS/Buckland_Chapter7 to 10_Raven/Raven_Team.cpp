#include "Raven_Team.h"
#include "Raven_Bot.h"

#include <algorithm>

Raven_Team::Raven_Team(Raven_Bot* leader) : m_pTeamLeader(leader)
{
	//The leader also belong to the team
	AddToTeam(leader);
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
