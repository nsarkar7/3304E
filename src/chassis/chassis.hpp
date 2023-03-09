#pragma once

#include <memory>

#include "main.h"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "pros/imu.hpp"
#include "constants.hpp"

namespace src::Chassis {

    static constexpr float TURN_FACTOR = 0.65f;

    static MotorGroup left_chassis = {
        Motor(CHASSIS_PORT_LF, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees),
        Motor(CHASSIS_PORT_LM, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees),
        Motor(CHASSIS_PORT_LB, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees)};

    static MotorGroup right_chassis = {   
        Motor(CHASSIS_PORT_RF, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees),
        Motor(CHASSIS_PORT_RM, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees),
        Motor(CHASSIS_PORT_RB, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees)};

extern std::shared_ptr<ChassisController> chassis;
static okapi::Controller controller = okapi::Controller();

extern void initialize();

extern void update();

extern void act();

extern void movePID(float leftTarget, float rightTarget, int ms, float maxV = 1);

extern void turnPID(float degrees, bool CW, float maxV = 1);

extern void gyroPID(int degree, bool CW, int ms = 1000);

extern void lv_ex_chart_1(float kP, float kI, float kD, int ms);
}