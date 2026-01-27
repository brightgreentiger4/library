#include "lib.h"
#include "main.h"

const double Pi = 3.145
namespace e_lib {
class Chassis {
    private:
        pros::MotorGroup leftMG;
        pros::MotorGroup rightMG;
        double chassisWidth;
        double wheelGearRatio;
    public:
        Chassis(pros::MotorGroup left, pros::MotorGroup right, double width, double wheelDia ,double gearRatio) {
            leftMG = left;
            rightMG = right;
            chassisWidth = width;
            wheelGearRatio = gearRatio;
        };

        void turn(const double degrees, const double radius, const double velocity, const int dir) {
            double proportionOfCircle = 360/degrees
            double baseDist = 2*radius*Pi*position*wheelGearRatio*proportionOfCircle // 2PIR * proportion
            
            double offsetDist = 2*chassisWidth*Pi*position*wheelGearRatio*proportionOfCircle*dir // added perimeter
            
            double goal = baseDist+offsetDist
            
            double velProportion = (baseDist-offsetDist)/(baseDist+offsetDist)
            
            leftMG.move_relative(baseDist+offsetDist, velocity)
            rightMG.move_relative(baseDist-offsetDist, velocity)
        }

        void move_relative(double position, double velocity) {
            
            double dist = position*wheelGearRatio
            
            leftMG.move_relative(dist, velocity)
        }
   
};
}