#ifndef FLIGHT_MODES_H
#define FLIGHT_MODES_H

/**
 * Enum containing all flight modes.
 * These tell the vehicle which kinematic 
 * parameters to control and if it should
 * be disarmed, armed or emergency shutdown.
 */
enum FLIGHT_MODE {
    //Disarms vehicle disabling motors and moving acuators into a home postion
    DISARMED,
    //Arms vehicle by enabling motors(at lowest throttle) and putting all actuators into flight ready postion
    ARMED,
    //Immediatly shuts everything down. Motors are disabled and actators stop moving.
    FAILSAFE,
    //Makes vehicle only follow rate commands.
    RATE_CONTROL,
    //Makes vehicle only follow attitude and rate commands.
    ATTITUDE_CONTROL,
    //Makes vehicle only follow velocity commands.
    VELOCITY_CONTROL,
    //Makes vehicle only follow position commands.
    POSITION_CONTROL
};



#endif
