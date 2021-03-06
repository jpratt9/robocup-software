
#pragma once

#include <Geometry2d/Point.hpp>
#include <Geometry2d/Segment.hpp>
#include <Geometry2d/CompositeShape.hpp>
#include <Configuration.hpp>

namespace Planning
{
	/**
	 * @brief Represents a motion path as a series of {pos, vel} pairs.
	 *
	 * @details The path represents a function of position given time that the robot should follow.  A
	 * line-segment-based path comes from the planner, then we use cubic bezier curves to interpolate
	 * and smooth it out.  This is done via the evaulate() method.
	 */
	class Path
	{
		public:

			/** default path is empty */
			Path() {}

			/** constructor with a single point */
			Path(const Geometry2d::Point& p0);

			/** constructor from two points */
			Path(const Geometry2d::Point& p0, const Geometry2d::Point& p1);

			bool empty() const
			{
				return points.empty();
			}
			
			void clear()
			{
				points.clear();
			}
			
			/**
			 * Calulates the length of the path 
			 *
			 * \param[in] 	start Index of point in path to use at start point.
			 * \returns 	the length of the path starting at point (start). 
			 */
			float length(unsigned int start = 0) const;
			
			/**
			 * Calulates the length of the path
			 *
			 * \param[in] 	start Index of point in path to use at start point.
			 * \param[in] 	end Index of point in path to use at end point.
			 * \returns 	the length of the path starting at point (start) and ending at point [end]. 
			 */
			float length(unsigned int start, unsigned int end) const;
			
			/** Returns the length of the path from the closet point found to @a pt */
			float length(const Geometry2d::Point &pt) const;
			
			/** Returns number of waypoints */
			size_t size() const { return points.size(); }

			/** returns true if the path has non-zero size */
			bool valid() const { return !points.empty(); }

			// Returns the index of the point in this path nearest to pt.
			int nearestIndex(const Geometry2d::Point &pt) const;
			
			/** returns the nearest segement of @a pt to the path */
			Geometry2d::Segment nearestSegment(const Geometry2d::Point &pt) const;
			
			// Returns the shortest distance from this path to the given point
			float distanceTo(const Geometry2d::Point &pt) const;
			
			// Returns the start of the path
			boost::optional<Geometry2d::Point> start() const;

			// Returns a new path starting from a given point
			void startFrom(const Geometry2d::Point& pt, Planning::Path& result) const;

			//Returns the destination of this path (the last point in the points array)
			boost::optional<Geometry2d::Point> destination() const;

			// Returns true if the path never touches an obstacle or additionally, when exitObstacles is true, if the path
			// starts out in an obstacle but leaves and never re-enters any obstacle.
			bool hit(const Geometry2d::CompositeShape &shape, unsigned int start = 0) const;
			
			// Set of points in the path - used as waypoints
			std::vector<Geometry2d::Point> points;
			std::vector<Geometry2d::Point> vels;
			std::vector<float> times;

			/**
			 * A path describes the position and velocity a robot should be at for a
			 * particular time interval.  This method evalates the path at a given time and
			 * returns the target position and velocity of the robot.
			 *
			 * @param[in] 	t Time (in seconds) since the robot started the path
			 * @param[out] 	targetPosOut The position the robot would ideally be at at the given time
			 * @param[out] 	targetVelOut The target velocity of the robot at the given time
			 * @return 		true if the path is valid at time @t, false if you've gone past the end
			 */
			bool evaluate(float t, Geometry2d::Point &targetPosOut, Geometry2d::Point &targetVelOut) const;

			/**
			 * Evaluates the point and velocity of the robot at a given distance in the path.
			 *
			 * @param[in] 	distance A given distance the robot has traveled down the path from the start or t=0
			 * @param[out] 	position The position the robot given distance in the path
			 * @param[out] 	direction The target velocity of the robot at the given distance in the path
			 * @return 		true if the path is valid at the given distance, false if you've gone past the end
			 */
			bool getPoint(float distance ,Geometry2d::Point &position, Geometry2d::Point &direction) const;

			/**
			 * Estimates how long it would take for the robot to get to a certain point in the path using 
			 * Trapezoidal motion.
			 *
			 * @param[in] 	index Index of the point on the path 
			 * @return 		the estimated time it would take for the robot to a point on the path starting from the start of the path
			 */
			float getTime(int index) const;
			static void createConfiguration(Configuration *cfg);

			Geometry2d::Point vi;	//Stored velocity of the robot at the start of the path
			Geometry2d::Point vf;	//Stored target end velocity of the robot at the end of the path


			float startSpeed = 0; 	//Stored speed of the robot at the start of the path
			float endSpeed = 0;		//Stored target endSpeed of the robot at teh end of hte path.

			///	note: you MUST set these before calling evaluate or else it'll throw an exception
			float maxSpeed = -1;
			float maxAcceleration = -1;
	};
}
