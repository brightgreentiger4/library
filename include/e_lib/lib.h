// lib.h

#include "main.h"

#ifndef Chassis
#define Chassis

namespace e_lib {
class Chassis

    public:
    /**
	 * Creates a new Chassis object
     * Requires 2 MotorGroups: Left and Right
     * Requires a distance between the two MotorGroups (turn rate)
     * (pros::MotorGroup left, pros::MotorGroup right, float distance)
     * \param left
     * LEFT MG
     * \param right
     * RIGHT MG
     * \param distance
	 * DISTANCE BETWEEN TWO WHEEL DRIVES
	 */

    Chassis(pros::MotorGroup left, pros::MotorGroup right, float dist);

    /**
	 * Sets the relative target position for the chassis to move to.
	 *
	 * This movement is relative to the current position of each motor as given in
	 * pros::MotorGroup::get_position(). Providing 10.0 as the position parameter
	 * would result in the motor moving 10 units, no matter what the
	 * current position is.
	 *
	 *
	 *
	 * \param position
	 *        The relative position to move to in the motor's encoder units
	 * \param velocity
	 *        The maximum allowable velocity for the movement in RPM
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation
	 * failed, setting errno.
	 
	 */

    std::int32_t move_relative(const double position, const std::int32_t velocity) const;

    std::int32_t turn(const double radius, const double degrees)

}