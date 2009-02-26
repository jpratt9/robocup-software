#include "WorldModel.hpp"

#include <QObject>
#include <vector>

#include "RobotWM.hpp"
#include "framework/Module.hpp"
//#include "Ball.hpp"

using namespace Modeling;

WorldModel::WorldModel() :
	Module("World Model")
{

//   blueTeam = new std::vector<Robot*>;
//   yellowTeam = new std::vector<Robot*>;
//   for (unsigned int i = 0; i<5; ++i) 
//     {
//     blueTeam->push_back(new Robot());
//     yellowTeam->push_back(new Robot());
//     }
//   ball = new Ball();

}


void WorldModel::run()
{
	Q_FOREACH(const Packet::Vision& vision, _state->rawVision)
	{
		if (!vision.sync)
		{
			const std::vector<Packet::Vision::Robot>* self = &vision.blue;
			const std::vector<Packet::Vision::Robot>* opp = &vision.yellow;
			
			if (!_state->isBlue)
			{
				self = &vision.yellow;
				opp = &vision.blue;
			}
			
			//index is the id
			Q_FOREACH (const Packet::Vision::Robot& r, *self)
			{
				//get data from vision packet
				_self[r.shell]._shell = r.shell;
				_self[r.shell]._measPos = r.pos;
				_self[r.shell]._measAngle = r.angle;
				_self[r.shell]._valid = true;

				//get data from commands
				_self[r.shell]._cmdPos = _state->self[r.shell].cmdPos;
				_self[r.shell]._cmdVel = _state->self[r.shell].cmdVel;
				_self[r.shell]._cmdAngle = _state->self[r.shell].cmdAngle;
			  
				//process world model
				_self[r.shell].process();

				//store data back in state variable
				_state->self[r.shell].shell = _self[r.shell]._shell;
				_state->self[r.shell].pos = _self[r.shell]._pos;
				_state->self[r.shell].vel = _self[r.shell]._vel;
				_state->self[r.shell].angle = _self[r.shell]._posAngle;
				_state->self[r.shell].angleVel = _self[r.shell]._velAngle;
				_state->self[r.shell].valid = true;
			}
			//index is the id
			Q_FOREACH (const Packet::Vision::Robot& r, *opp)
			{
				//get data from vision packet
				_opp[r.shell]._shell = r.shell;
				_opp[r.shell]._measPos = r.pos;
				_opp[r.shell]._measAngle = r.angle;
				_opp[r.shell]._valid = true;
				//Note that control information cannot be used for opp

				//process world model
				_opp[r.shell].process();

				//store data back in state variable
				_state->self[r.shell].shell = _opp[r.shell]._shell;
				_state->self[r.shell].pos = _opp[r.shell]._pos;
				_state->self[r.shell].vel = _opp[r.shell]._vel;
				_state->self[r.shell].angle = _opp[r.shell]._posAngle;
				_state->self[r.shell].angleVel = _opp[r.shell]._velAngle;
				_state->self[r.shell].valid = true;
			}
			
			//copy ball
			if (vision.balls.size() > 0)
			{
				_state->ball.pos = vision.balls.at(1).pos;
			}
		}
	}
}