#include "e_lib/lib.hpp"
#include "main.h"

const double Pi = 3.145;
namespace e_lib {

    Chassis::Chassis(std::vector<std::int8_t> left, std::vector<std::int8_t> right, double width, double wheelDia ,double gearRatio) : leftPorts(left), rightPorts(right), chassisWidth(width), wheelGearRatio(gearRatio) 
    {};

    void Chassis::turnWithRadius(const double degrees, const double radius, double velocity, const int dir) {
        pros::MotorGroup leftMG(leftPorts);
        pros::MotorGroup rightMG(rightPorts);

        double proportionOfCircle = 360/degrees;
        double baseDist = 2*radius*Pi*wheelGearRatio*proportionOfCircle; // 2PIR * proportion
        
        double offsetDist = 2*chassisWidth*Pi*wheelGearRatio*proportionOfCircle; // added perimeter
        
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
        while ((leftMG.get_position() > leftMGMovement-5) && (leftMG.get_position() < leftMGMovement+5))  {
            pros::delay(20);
        };
        while ((rightMG.get_position() > rightMGMovement-5) && (leftMG.get_position() < rightMGMovement+5))  {
            pros::delay(20);
        };
    }

    void Chassis::move_relative(double position, double velocity) {
        pros::MotorGroup leftMG(leftPorts);
        pros::MotorGroup rightMG(rightPorts);

        double dist = position*wheelGearRatio;
        
        leftMG.move_relative(dist, velocity);
        rightMG.move_relative(dist, velocity);
    }
}