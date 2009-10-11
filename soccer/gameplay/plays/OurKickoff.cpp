#include "OurKickoff.hpp"

using namespace std;

Gameplay::Plays::OurKickoff::OurKickoff(GameplayModule *gameplay):
	Play(gameplay),
	_kicker(gameplay),
	_idle1(gameplay),
	_idle2(gameplay),
	_idle3(gameplay)
{
}

bool Gameplay::Plays::OurKickoff::applicable()
{
	return gameState().setupRestart() && gameState().ourKickoff();
}

void Gameplay::Plays::OurKickoff::assign(set<Robot *> &available)
{
	_idle1.target = _gameplay->centerMatrix() * Geometry2d::Point(0.7, -0.2);
	_idle2.target = _gameplay->centerMatrix() * Geometry2d::Point(-0.7, -0.2);
	_idle3.target = Geometry2d::Point(0, 1.5);
	
	_kicker.assign(available);
	_idle1.assign(available);
	_idle2.assign(available);
	_idle3.assign(available);
}

bool Gameplay::Plays::OurKickoff::run()
{
	_idle1.face = ball().pos;
	_idle2.face = ball().pos;
	_idle3.face = ball().pos;
	
	_kicker.run();
	_idle1.run();
	_idle2.run();
	_idle3.run();
	
	return true;
}