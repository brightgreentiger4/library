#include "lib.h"
#include "main.h"

double Pi = 3.145

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

        void turn(double degrees, double radius) {
            
        }

        void move_relative(double position, double velocity) {
            
            double dist = position*wheelGearRatio
            
            leftMG.move_relative(dist, velocity)
        }
   
};
