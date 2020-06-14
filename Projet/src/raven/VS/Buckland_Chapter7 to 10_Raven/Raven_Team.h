#ifndef RAVEN_TEAM_H
#define RAVEN_TEAM_H

#include <vector>

class Raven_Bot;


class Raven_Team
{
private:

	std::vector<Raven_Bot*> m_vecTeamMembers;

	Raven_Bot* m_pTeamLeader;

public:

	//Constructor
	Raven_Team(Raven_Bot* leader);
	~Raven_Team();

	//Return if the given bot belongs to that team
	bool IsInTeam(Raven_Bot* const bot) const;

	bool IsLeader(Raven_Bot* const bot) const { return bot == m_pTeamLeader; }

	//Add the bot to the team if not already in it
	void AddToTeam(Raven_Bot* const bot);

	//Remove the bot from the team. Return true if successful, false if it wasn't in the team.
	void RemoveFromTeam(Raven_Bot* const bot);

	//Set a new leader, but the old stay in the team.
	Raven_Bot* SetLeader(Raven_Bot* newLeader) { 
		m_pTeamLeader = newLeader;
		m_vecTeamMembers.push_back(newLeader);
	}

	Raven_Bot* GetLeader() const { return m_pTeamLeader; }
	int		   GetSize() const { return m_vecTeamMembers.size(); }


};

#endif
