#ifndef FEEDER_SUBSYSTEM_HPP_
#define FEEDER_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "modm/math/filter/pid.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"

#ifdef TARGET_STANDARD
#include "controls/standard/standard_constants.hpp"
#endif


#ifdef TARGET_HERO
#include "controls/hero/hero_constants.hpp"
#endif

#ifdef TARGET_SENTRY
#include "controls/sentry/sentry_constants.hpp"
#endif

#include "drivers.hpp"

namespace feeder{

class FeederSubsystem : public tap::control::Subsystem
{
public:
    FeederSubsystem(tap::Drivers *drivers)
    : tap::control::Subsystem(drivers),
    feederMotor(drivers,
               constants.FEEDER_MOTOR_ID,
               constants.CAN_BUS,
               false,
               "Feeder Motor"),
      targetRPM(0.0f),
      currentFeederMotorSpeed(0.0f),
      rpmPid(feederPid.PID_KP, feederPid.PID_KI, feederPid.PID_KD,
      feederPid.PID_MAX_IOUT, feederPid.PID_MAX_OUT)
      {}

    void initialize() override;
    void refresh() override;

    const char* getName() override {return "feeder subsystem";}

    void setTargetRPM(float RPM);

    float getFeederMotorRPM() const {return feederMotor.isMotorOnline() ? feederMotor.getShaftRPM() : 0.0f; }

    void updateFeederPid(modm::Pid<float>* pid, tap::motor::DjiMotor* const motor, float desiredRpm);

    bool motorOnline(){ return feederMotor.isMotorOnline();
    }

private:
    tap::motor::DjiMotor feederMotor;

    //target RPM, idk the range of its value
    float targetRPM;

    //motor speed given in revolutions / min
    float currentFeederMotorSpeed;

    modm::Pid<float> rpmPid;

    //PID constants
    FEEDER_PID feederPid;

    //feeder constants
    Feeder_CONSTANTS constants;

};  //class FeederSubsystem

}   //namespace feeder

#endif