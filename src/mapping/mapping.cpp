#include "mapping.hpp"

#include "common.h"
#include "okapi/impl/device/motor/motor.hpp"
#include "pros/rtos.hpp"
#include "constants.hpp"

#include <iostream>
#include<fstream>
#include <string>

using namespace std;

namespace src::Mapping {
    

    void log(void *) {

        FILE* ext_storage_file = fopen("/usd/skills.txt", "w");

        int timer = 0;

        if (ext_storage_file == NULL) {
            printf("Error: Failed to open external storage\n");
            return;
        }

        while(true){

            string str = 
            
                to_string(chassis1Motor.getActualVelocity()) + "," + 
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

            fprintf(ext_storage_file, "%s",str);

            timer = timer + LOG_INTERVAL;

            if((TIME_LIMIT * 1000) >= timer) {
                printf("Success! Logged motor/piston values to external storage\n");
                fflush(ext_storage_file);
                fclose(ext_storage_file);
                return;
            }

            pros::delay(LOG_INTERVAL);
        }

    }

    void initialize() {
        pros::Task DriverMappingTask(log);

    }

    int file_line_count(string file_path) {
        int count = 0;
        string line;
        ifstream file(file_path);
        
        while (getline(file, line)) {
            count++;
        }

        return count;
    }

}