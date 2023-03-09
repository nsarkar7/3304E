#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/vision.hpp"
#include "constants.hpp"

namespace src::Mech {

    enum class IntakeStates {
        OFF = 0,
        INTAKE = 1,
        OUTAKE = 2,
    };

    enum class ExpansionStates {
        IN = 0,
        OUT = 1,
    };

    enum class FlywheelStates {
        OFF = 0,
        ON = 1,
    };

    enum class IndexerStates {
        IN = 0,
        OUT = 1,
    };

    extern void initialize();
    extern void update();
    extern void act();

    static Motor flywheelMotor = Motor(FLYWHEEL_PORT, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    static Motor intakeMotor = Motor(INTAKE_PORT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

    static pros::ADIDigitalOut indexer = pros::ADIDigitalOut(INDEXER_PORT, static_cast<bool>(IndexerStates::OUT));
}