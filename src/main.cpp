#include "chassis/chassis.hpp"
#include "okapi/impl/device/controller.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "mech/mech.hpp"
#include "mapping/mapping.hpp"
#include <cstdlib>

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}


void disabled() {}


void competition_initialize() {}


void autonomous() {}


void opcontrol() {
	src::Chassis::initialize();
	src::Mech::initialize();

	while (true) {
		src::Mech::update();
		src::Chassis::update();
		src::Mech::act();
		src::Chassis::act();

		pros::delay(10);
	}
}
