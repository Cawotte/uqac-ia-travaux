#include "Raven_TeamArea.h"

#include "Raven_Team.h"
#include "misc/Cgdi.h"
#include "misc/utils.h"

Raven_TeamArea::Raven_TeamArea(Vector2D position, double size, Raven_Team* team) :
	m_center(position),
	m_sizeArea(size),
	m_team(team)
{
}
double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
Vector2D Raven_TeamArea::GetRandomPositionInsideArea()
{

	double randXOffset = RandInRange(-m_sizeArea, m_sizeArea);
	double randYOffset = RandInRange(-m_sizeArea, m_sizeArea);

	return m_center + Vector2D(randXOffset, randYOffset);
}

void Raven_TeamArea::Render() const
{
	Vector2D corners[4] =
	{
		m_center + Vector2D(-m_sizeArea, -m_sizeArea), //top left
		m_center + Vector2D(-m_sizeArea, m_sizeArea), //top right
		m_center + Vector2D(m_sizeArea, m_sizeArea), //bottom right
		m_center + Vector2D(m_sizeArea, -m_sizeArea), //bottom left
	};

	m_team->UseTeamColor();

	for (int i = 0; i < 4; i++)
	{
		Vector2D a = corners[i];
		Vector2D b = corners[(i + 1) % 4];

		gdi->Line(a.x, a.y, b.x, b.y);
	}
}
