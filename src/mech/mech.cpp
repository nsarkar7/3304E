#include "mech.hpp"

#include "common.h"
#include "okapi/api/control/async/asyncVelIntegratedController.hpp"
#include "okapi/impl/device/button/controllerButton.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "pros/rtos.hpp"
#include "constants.hpp"
#include <string>
#include <map>

namespace src::Mech {

    ControllerButton flywheelToggle(ControllerDigital::X);
    ControllerButton indexerBtn(ControllerDigital::L1);
    ControllerButton rapidFireBtn(ControllerDigital::L2);
    ControllerButton intakeBtn(ControllerDigital::R1);
    ControllerButton outtakeBtn(ControllerDigital::R2);
    ControllerButton expansionBtn(ControllerDigital::up);

    FlywheelStates currFlywheelState = FlywheelStates::OFF;
    IntakeStates currIntakeState = IntakeStates::OFF;
    IndexerStates currIndexerState = IndexerStates::OUT;
    ExpansionStates currExpansionState = ExpansionStates::IN;

    std::map<int, int> piston_states = {
    { 1, 1},
    { 2, 0},
    { 3, 0}
};


    float targetFlywheelRpm = 0;
    void flywheelVelocityControl(void *) {
        while(true) {
            if (targetFlywheelRpm == 0) {
                flywheelMotor.moveVoltage(0);
                pros::delay(10);
                continue;
            }
            float error = targetFlywheelRpm - (flywheelMotor.getActualVelocity() * 5.0f);
            float threshholdRpm = 30.0f;
            if(error > (targetFlywheelRpm - threshholdRpm)) {
                flywheelMotor.moveVoltage(12000);
            } else if (error <= -threshholdRpm) {
                flywheelMotor.moveVoltage(0);
            } 
            else {
                flywheelMotor.moveVoltage((targetFlywheelRpm * 4.0f) + (error * 1.0f));
            }

            pros::delay(1);
        }
    }
    
    void initialize() {
        flywheelMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
        intakeMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
        pros::Task FlywheelVelocityControlTask(flywheelVelocityControl);
    }

    void shoot(int delay) {
        indexer.set_value(static_cast<bool>(IndexerStates::IN));
        piston_states.find(1)->second = 0;

        pros::delay(100);

        indexer.set_value(static_cast<bool>(IndexerStates::OUT));
        piston_states.find(1)->second = 1;
        pros::delay(delay);
    }

    void update() {
        currIntakeState = IntakeStates::OFF;

        if (flywheelToggle.changedToPressed()) {
            if (currFlywheelState == FlywheelStates::OFF) {
                currFlywheelState = FlywheelStates::ON;
            } else {
                currFlywheelState = FlywheelStates::OFF;
            }
        }

        if (indexerBtn.controllerGet() == true) {
            shoot(300);
        }
        if (rapidFireBtn.controllerGet() == true) {
            shoot(300);
            shoot(500);
            shoot(0);
        }
        if (intakeBtn.controllerGet() == true) {
            currIntakeState = IntakeStates::INTAKE;
        }

        if (outtakeBtn.controllerGet() == true) {
            currIntakeState = IntakeStates::OUTAKE;
        }

        if (expansionBtn.controllerGet() == true) {
            currExpansionState = ExpansionStates::OUT;
        }
    }

    void act() {
        switch (currIntakeState) {
            case IntakeStates::INTAKE:
                intakeMotor.moveVoltage(12000);
                break;
            case IntakeStates::OUTAKE:
                intakeMotor.moveVoltage(-12000);
                break;
            case IntakeStates::OFF:
                intakeMotor.moveVoltage(0);
                break;
        }

        switch (currFlywheelState) {
            case FlywheelStates::ON:
                targetFlywheelRpm = 1925;
                break;
            case FlywheelStates::OFF:
                targetFlywheelRpm = 0;
                break;
        }

        switch (currExpansionState) {
            case ExpansionStates::IN:
                expansion1.set_value(static_cast<bool>(ExpansionStates::IN));
                expansion2.set_value(static_cast<bool>(ExpansionStates::IN));
                piston_states.find(2)->second = 0;
                piston_states.find(3)->second = 0;
                break;
            case ExpansionStates::OUT:
                expansion1.set_value(static_cast<bool>(ExpansionStates::OUT));
                expansion2.set_value(static_cast<bool>(ExpansionStates::OUT));
                piston_states.find(2)->second = 1;
                piston_states.find(3)->second = 1;
                break;
        }
    }
}