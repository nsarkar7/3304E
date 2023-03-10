#include "mapping.hpp"

#include "common.h"
#include "okapi/impl/device/motor/motor.hpp"
#include "pros/rtos.hpp"
#include "constants.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace src::Mapping {
    
    FILE* ext_storage = fopen("/usd/skills.txt", "w");

    void log(void *) {
        while(true){
            string str = to_string(chassis1Motor.getActualVelocity()) + "," + 
            to_string(chassis2Motor.getActualVelocity()) + "," + 
            to_string(chassis3Motor.getActualVelocity()) + "," + 
            to_string(chassis4Motor.getActualVelocity()) + "," + 
            to_string(chassis5Motor.getActualVelocity()) + "," + 
            to_string(chassis6Motor.getActualVelocity()) + "," + 
            to_string(flywheelMotor.getActualVelocity()) + "," + 
            to_string(intakeMotor.getActualVelocity()) + "," +
            to_string(src::Mech::piston_states.find(1)->second) + "," +
            to_string(src::Mech::piston_states.find(2)->second) + "," +
            to_string(src::Mech::piston_states.find(3)->second) + "\n";

            fprintf(ext_storage, "%s",str);
        }
    }

    void initialize() {
        pros::Task DriverMappingTask(log);

    }
}