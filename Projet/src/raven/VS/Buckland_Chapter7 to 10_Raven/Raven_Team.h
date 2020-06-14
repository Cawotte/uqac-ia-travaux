#ifndef RAVEN_TEAM_H
#define RAVEN_TEAM_H

#include <vector>

class Raven_Bot;


class Raven_Team
{
private:

	//Hack for team colors
	static int teamCount;

	int m_teamID;

	//vector with all members to the team (including leader)
	std::vector<Raven_Bot*> m_vecTeamMembers;

	//leader of the team
	Raven_Bot* m_pTeamLeader;

	//Whoever their are, the team wan them DEAD
	Raven_Bot* m_pTarget;

	void GetTeamColor(int teamID);

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

	void UseTeamColor();

	//Set a new leader, but the old stay in the team.
	void SetLeader(Raven_Bot* newLeader) {
		m_pTeamLeader = newLeader;
		m_vecTeamMembers.push_back(newLeader);
	}

	void SetTarget(Raven_Bot* newTarget) {
		m_pTarget = newTarget;
	}

	Raven_Bot* GetLeader() const { return m_pTeamLeader; }
	Raven_Bot* GetTarget() const { return m_pTarget; }
	int		   GetSize() const { return m_vecTeamMembers.size(); }

	bool	   HasTarget() const { return m_pTarget != NULL;  }

};

#endif
