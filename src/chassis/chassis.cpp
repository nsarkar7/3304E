#include "chassis.hpp"

#include "main.h"

#include "pros/misc.h"
#include "constants.hpp"

namespace src::Chassis {

    // Driver Control
    std::shared_ptr<ChassisController> chassis =
        ChassisControllerBuilder()
            .withMotors(left_chassis, right_chassis)
            .withDimensions(AbstractMotor::gearset::blue, {{WHEEL_DIAMETER, WHEEL_TRACK}, imev5BlueTPR})
            .build();
    
    void initialize() {
        left_chassis.setBrakeMode(AbstractMotor::brakeMode::coast);
        right_chassis.setBrakeMode(AbstractMotor::brakeMode::coast);
    }

    void update() {}

    void act() {
        Chassis::chassis->getModel()->tank(
            controller.getAnalog(ControllerAnalog::leftY),
            controller.getAnalog(ControllerAnalog::rightY));
    }

    pros::Imu imuSensor = pros::Imu(IMU_PORT);

    // curves + straight
    void movePID(float leftTarget, float rightTarget, int ms, float maxV) {
        float degreesR = ((rightTarget/(pi*WHEEL_DIAMETER)) * 360) / DRIVE_GEAR_RATIO;
        float degreesL = ((leftTarget/(pi*WHEEL_DIAMETER)) * 360) / DRIVE_GEAR_RATIO;

        // Create PID controllers for each side of the chassis
        auto drivePIDL = okapi::IterativeControllerFactory::posPID(P_GAIN, I_GAIN, D_GAIN);
        auto drivePIDR = okapi::IterativeControllerFactory::posPID(P_GAIN, I_GAIN, D_GAIN);
        
        // Reset Chassis sensors
        chassis->getModel()->resetSensors();
        
        // Initialize loop variables
        int timer = 0;
        float errorL;
        float errorR;
        float powerL;
        float powerR;

        // Within time limit, increment PID loop
        while (timer < ms) {
            errorL = degreesL + chassis->getModel()->getSensorVals()[0];
            errorR = degreesR + chassis->getModel()->getSensorVals()[1];
            powerL = drivePIDL.step(errorL);
            powerR = drivePIDR.step(errorR);
            chassis->getModel()->tank(powerL * maxV, powerR * maxV);
            pros::delay(10);
            timer += 10;
        }

        chassis->getModel()->tank(0, 0);
    }

    // no imu
    void turnPID(float degrees, bool CW, float maxV) {
        
        float turningCircleCircumference = M_PI * WHEEL_TRACK;
        float wheelDistance = (degrees / 360.0f) * (turningCircleCircumference / 2.0f);

        // Turns should always take at least 1 second
        int turnTimer = 1500;
        
        if (!CW) {
            movePID(wheelDistance, -1 * wheelDistance, turnTimer, maxV);
        } else {
            movePID(-1 * wheelDistance, wheelDistance, turnTimer, maxV);
        }
    }

    //IMU (clockwise only)
    void gyroPID(int degree, bool CW, int ms) {

        imuSensor.tare_rotation();
        int timer = 0;
        float prevError = 0;
        float integral = 0;
        src::Chassis::controller.clear();
        while (timer < ms) {
            float sensorVal = imuSensor.get_rotation();
            pros::screen::print(pros::E_TEXT_LARGE, 0, "gyro: %f", sensorVal);
            float error = degree - sensorVal;
            float derivative = error - prevError;
            prevError = error;
            integral += error;
            float power = (P_GAIN_TURN * error) + (I_GAIN_TURN * integral) + (D_GAIN_TURN * derivative);
            
            if (CW) {
                chassis->getModel()->tank(power, -1 * power);
            } else {
                chassis->getModel()->tank(-1 * power, power);
            }
            timer += 10;
            pros::delay(10);

        }
        chassis->getModel()->tank(0, 0);
    }

}