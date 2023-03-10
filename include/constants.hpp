#pragma once
#include "main.h"

// Motor Ports
static constexpr uint8_t CHASSIS_PORT_LF = 13;
static constexpr uint8_t CHASSIS_PORT_LM = 14;
static constexpr uint8_t CHASSIS_PORT_LB = 15;

static constexpr uint8_t CHASSIS_PORT_RF = 16;
static constexpr uint8_t CHASSIS_PORT_RM = 17;
static constexpr uint8_t CHASSIS_PORT_RB = 18;

static constexpr uint8_t FLYWHEEL_PORT = 11;
static constexpr uint8_t INTAKE_PORT = 12;

//3 Wire Ports

static constexpr uint8_t INDEXER_PORT = 'H';
static constexpr uint8_t EXPANSION_1_PORT = 'F';
static constexpr uint8_t EXPANSION_2_PORT = 'G';

// Sensor Ports

static constexpr uint8_t IMU_PORT = 21;

// Physical Constants
static constexpr float_t WHEEL_DIAMETER = 3.25f;        // [in]
static constexpr float_t CENTER_TO_LEFT_ENCODER = 0.0f;  // [in]
static constexpr float_t CENTER_TO_RIGHT_ENCODER = 0.0f; // [in]
static constexpr float_t CENTER_TO_BACK_ENCODER = 0.0f;  // [in]
static constexpr float_t WHEEL_TRACK = 12.5984f;         // [in]
static constexpr float_t DRIVE_GEAR_RATIO = 72.0f / 48.0f;

// Programming Constants
static constexpr float TURN_FACTOR = 0.65f;
static constexpr float P_GAIN = 0.005f;
static constexpr float I_GAIN = 0.00001f;
static constexpr float D_GAIN = 0.00025f;
static constexpr float P_GAIN_TURN = 0.05f;
static constexpr float I_GAIN_TURN = 0.000008f;
static constexpr float D_GAIN_TURN = 0.16f;//0.15

// Driver Mapping Constants
static constexpr float TIME_LIMIT = 60; //seconds
static constexpr float LOG_INTERVAL = 1; //msecs
