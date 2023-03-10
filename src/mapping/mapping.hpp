#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/vision.hpp"
#include "constants.hpp"
#include "../src/mech/mech.hpp"

namespace src::Mapping {

    extern void initialize();
    extern void update();
    extern void act();

    static Motor chassis1Motor = Motor(CHASSIS_PORT_LF, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor chassis2Motor = Motor(CHASSIS_PORT_LM, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor chassis3Motor = Motor(CHASSIS_PORT_LB, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor chassis4Motor = Motor(CHASSIS_PORT_RF, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor chassis5Motor = Motor(CHASSIS_PORT_RM, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor chassis6Motor = Motor(CHASSIS_PORT_RB, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    
    static Motor flywheelMotor = Motor(FLYWHEEL_PORT, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor intakeMotor = Motor(INTAKE_PORT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

}