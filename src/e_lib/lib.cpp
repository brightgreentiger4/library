#include "e_lib/lib.hpp"
#include "main.h"
#include "liblvgl\lvgl.h" // probably bad practice?
#include <string>
#include <queue>

const double Pi = 3.145;



namespace e_lib {

    Chassis::Chassis(std::vector<std::int8_t> left, std::vector<std::int8_t> right, double width, double wheelDia ,double gearRatio) : leftPorts(left), rightPorts(right), chassisWidth(width) {
        leftTrack = new pros::MotorGroup(left);
        rightTrack = new pros::MotorGroup(right);
        wheelGearRatio =gearRatio/(Pi*wheelDia); //  1/circumference (so spinning 1 unit should be not in pi)
    };

    void Chassis::turn(const double degrees, const double radius, double velocity, const int dir) {
        //pros::MotorGroup leftMG(leftPorts);
        //pros::MotorGroup rightMG(rightPorts);

        pros::MotorGroup& leftMG = *leftTrack;
        pros::MotorGroup& rightMG = *rightTrack;

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
        while ((leftMG.get_position() < leftMGMovement-5) || (leftMG.get_position() > leftMGMovement+5))  {
            pros::delay(20);
        };
        while ((rightMG.get_position() < rightMGMovement-5) || (leftMG.get_position() > rightMGMovement+5))  {
            pros::delay(20);
        };
    }

    void Chassis::move_relative(double position, double velocity) {
        pros::MotorGroup& leftMG = *leftTrack;
        pros::MotorGroup& rightMG = *rightTrack;

        double dist = position*wheelGearRatio;
        
        leftMG.tare_position();
        rightMG.tare_position();

        leftMG.move_relative(dist, velocity);
        rightMG.move_relative(dist, velocity);

        while ((leftMG.get_position() < dist-5) || (leftMG.get_position() > dist+5)) {
            pros::delay(20);
        };

    }

    static lv_obj_t* diagnosticLabel;
    static std::string outputStream = "";
    static std::queue<int> lineLengths = {};
    static int lines = 0;
    void printToLabel(std::string s) {

        int lastBreak = 0;
        for (int i=0; i<size(s); i++) {
            if (s[i] == '\n') {
                // handle linebreaks by adding to lines
                lines++;
                lineLengths.push(i-lastBreak+1);
                lastBreak = i +1;
            }
        }

	outputStream += s + "\n";
	lines++;
	lineLengths.push(size(s)+1-lastBreak);
	while (lines > 12) {
		outputStream.erase(0, lineLengths.front());
		lineLengths.pop();
        lines--;
	}
	lv_label_set_text_fmt(diagnosticLabel, outputStream.c_str());
}
    
    void init() {
        lvgl_init();
        diagnosticLabel = lv_label_create(lv_screen_active());
        lv_label_set_text(diagnosticLabel, "");
        lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_align(diagnosticLabel, LV_ALIGN_TOP_LEFT, 0, 0);
	    lv_obj_set_size(diagnosticLabel, 720, 420);
        printToLabel("E-Lib successfully initialized print functionality");
    }
}