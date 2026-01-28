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
            double proportionOfCircle = 360/degrees;
            double baseDist = 2*radius*Pi*position*wheelGearRatio*proportionOfCircle; // 2PIR * proportion
            
            double offsetDist = 2*chassisWidth*Pi*position*wheelGearRatio*proportionOfCircle; // added perimeter
            
            double goal = baseDist+offsetDist;
            
            double velProportion = (baseDist-offsetDist)/(baseDist+offsetDist); // velocity reduction for inner section
            
            if (dir == -1) {
                velocity *= velProportion;
                velProportion = 1/velProportion; // LARGER NUMBER
            };
            
            leftMG.tare_position_all();
            rightMG.tare_position_all();
            double leftMGMovement =  baseDist+offsetDist*dir;
            double rightMGMovement =  baseDist-offsetDist*dir;
            leftMG.move_relative(leftMGMovement, velocity);
            rightMG.move_relative(rightMGMovement, velocity*velProportion);

            // YIELD
            while (leftMG.get_position() > leftMGMovement-5) && (leftMG.get_position() < leftMGMovement+5)  {
                pros::delay(20);
            };
           while (rightMG.get_position() > rightMGMovement-5) && (leftMG.get_position() < rightMGMovement+5)  {
                pros::delay(20);
            };
        }

        void move_relative(double position, double velocity) {
            
            double dist = position*wheelGearRatio;
            
            leftMG.move_relative(dist, velocity);
            rightMG.move_relative(dist, velocity);
        }
   
};
}