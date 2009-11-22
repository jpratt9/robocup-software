#include "OptimizedOffense.hpp"

using namespace std;

Gameplay::Plays::OptimizedOffense::OptimizedOffense(GameplayModule *gameplay):
	Play(gameplay)
{
}

bool Gameplay::Plays::OptimizedOffense::applicable()
{
	/** Replace this with code to determine whether this play is applicable now */
	return true;
}

void Gameplay::Plays::OptimizedOffense::assign(set<Robot *> &available)
{
	// this play always takes all available robots
	this->takeAll(available);
}

bool Gameplay::Plays::OptimizedOffense::run()
{
	if (planReady_) {
		// do small check of viability
		// if acceptable, run the underlying behavior and return
		// otherwise, jump to new plan creation
	} else {
		// create a new plan
	}
	return true;
}
