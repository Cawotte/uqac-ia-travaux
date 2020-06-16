
#ifndef RAVEN_TEAM_AREA_H
#define RAVEN_TEAM_AREA_H

#include <2D\Vector2D.h>

class Raven_Team;

class Raven_TeamArea
{
private:

	Vector2D m_center;
	double	 m_sizeArea;

	Raven_Team* m_team;

public:

	Raven_TeamArea(Vector2D position, double size, Raven_Team* team);

	Vector2D GetRandomPositionInsideArea();

	void Render() const;
};

#endif

