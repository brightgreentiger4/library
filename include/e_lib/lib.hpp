// lib.h
#pragma once
#include "main.h"

namespace e_lib {

class Chassis{ 
	private:
		std::vector<std::int8_t> leftPorts; // SINCE WE CANT STORE A PROS::MOTORGROUP DIRECTLY, WE STORE PORTS.
		std::vector<std::int8_t> rightPorts; // THIS IS SIMILAR TO EVERY OTHER LIBRARY
		double chassisWidth;
		double wheelGearRatio;
    public:
    /**
	 * Creates a new Chassis object
     * Requires 2 MotorGroups: Left and Right
     * Requires a distance between the two MotorGroups (for turning)
     * @param left
     * LEFT MG
     * @param right
     * RIGHT MG
     * @param width
	 * DISTANCE BETWEEN TWO WHEEL SIDES
	 * @param wheel
	 * WHEEL DIAMETER
	 * @param gearRatio
	 * GEAR RATIO
	 */

    Chassis(std::vector<std::int8_t> left, std::vector<std::int8_t> right, double width, double wheelDia, double gearRatio);

    /**
	 * Moves the chassis forward by distance.
	 *
	 * This movement is relative to the current position of each motor as given in
	 * pros::MotorGroup::get_position(). Providing 10.0 as the position parameter
	 * would result in the chassis moving 10 in, no matter what the
	 * current position is.
	 * @param position
	 *        The relative position to move
	 * @param velocity
	 *        The maximum allowable velocity for the movement in RPM
	 */

    void move_relative(const double position, const double velocity);

	/**
	 * Rotates the chassis along a curve.
	 * \param radius
	 * 		The turn circle of the chassis
	 * \param degrees
	 * 		The amount of degrees to rotate
	 * \param velocity
	 * The maximum allowable velocity for the motors to rotate in RPM
	 * \param dir
	 * The direction of turn. -1 or 1. Other values will break the robot. NO BOOLEAN TOO LAZY
	 */

    void turn(const double radius, const double degrees, const double velocity, int dir = 1);
	
};
}