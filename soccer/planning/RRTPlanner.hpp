
#pragma once

#include <list>
#include <Geometry2d/Point.hpp>
#include <Geometry2d/CompositeShape.hpp>
#include <planning/Path.hpp>
#include <MotionConstraints.hpp>

#include "Tree.hpp"

namespace Planning
{
	/** generate a random point on the floor */
	Geometry2d::Point randomPoint();

	/**
	 * @brief Given a start point and an end point and some conditions, plans a path for a robot to get there.
	 * 
	 * @details There are many ways to plan paths.  This planner uses bidirectional [RRTs](http://en.wikipedia.org/wiki/Rapidly-exploring_random_tree).
	 * You can check out our interactive RRT applet on GitHub here: https://github.com/RoboJackets/rrt.
	 */
	class RRTPlanner
	{
		public:
			RRTPlanner();
			/**
			 * gets the maximum number of iterations for the RRT algorithm
			 */
			int maxIterations() const
			{
				return _maxIterations;
			}
			/**
			 * sets the maximum number of iterations for th RRT algorithm
			 */
			void maxIterations(int value)
			{
				_maxIterations = value;
			}
			
			///run the path ROTplanner
			///this will always populate path to be the path we need to travel
			void run(
					const Geometry2d::Point& start,
					const float angle, 
					const Geometry2d::Point& vel, 
					const MotionConstraints &motionConstraints,
					const Geometry2d::CompositeShape* obstacles, 
					Planning::Path &path);
			
			/** returns the length of the best position planned path */
			float fixedPathLength() const { return _bestPath.length(); }
			
	protected:
		MotionConstraints _motionConstraints;

		FixedStepTree _fixedStepTree0;
		FixedStepTree _fixedStepTree1;
		
		/** best goal point */
		Geometry2d::Point _bestGoal;
		
		///best planned path
		///this is a fixed step path
		Planning::Path _bestPath;
		
		Geometry2d::Point vi;
		///maximum number of rrt iterations to run
		///this does not include connect attempts
		unsigned int _maxIterations;
		
		///latest obstacles
		const Geometry2d::CompositeShape* _obstacles;
		
		/** makes a path from the last point of each tree
		 *  If the points don't match up...fail!
		 *  The final path will be from the start of tree0
		 *  to the start of tree1 */
		void makePath();
		
		/** optimize the path 
		 *  Calles the cubicBezier optimization function.
		 */
		void optimize(Planning::Path &path, const Geometry2d::CompositeShape *obstacles);

		/**
		 * Uses a cubicBezier to interpolate between the points on the path and add
		 * velocity planning
		 */
		void cubicBezier(Planning::Path &path, const Geometry2d::CompositeShape *obstacles);

		/**
		 * Helper function for cubicBezier() which uses Eigen matrices to solve for the 
		 * cubic bezier equations.
		 */
		Eigen::VectorXd cubicBezierCalc (double vi, double vf, std::vector<double> &points, 
									std::vector<double> &ks, std::vector<double> &ks2);
	};
}
