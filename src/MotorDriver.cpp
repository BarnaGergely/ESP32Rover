#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <DRV8833.h>
#include <SimpleDebugLog.h>

#ifndef MOTOR_DRIVER_MAX_PWM
#define MOTOR_DRIVER_MAX_PWM 127
#endif

#ifndef MOTOR_DRIVER_MIN_PWM
#define MOTOR_DRIVER_MIN_PWM -127
#endif

#ifndef MOTOR_DRIVER_RAMP_TIME
#define MOTOR_DRIVER_RAMP_TIME 60
#endif

#ifndef MOTOR_DRIVER_NEUTRAL_WIDTH
#define MOTOR_DRIVER_NEUTRAL_WIDTH 60
#endif

#ifndef MOTOR_DRIVER_BRAKE
#define MOTOR_DRIVER_BRAKE false
#endif

#ifndef MOTOR_DRIVER_NEUTRAL_BRAKE
#define MOTOR_DRIVER_NEUTRAL_BRAKE false
#endif

class MotorDriver {
   public:
    /// @brief Sets the speed of the motor
    /// @param speed needs to bee between MOTOR_DRIVER_MIN_PWM and MOTOR_DRIVER_MIN_PWM. Negative speed means
    /// rotating backwards, 0 is to stop.
    /// @return 0 if successfully set, -1 if the given speed is not between MOTOR_DRIVER_MIN_PWM
    /// and MOTOR_DRIVER_MIN_PWM or if an error occurred
    int setSpeed(int speed) {
        if (speed < MOTOR_DRIVER_MIN_PWM || speed > MOTOR_DRIVER_MAX_PWM) {
            LOG_ERROR("[MotorDriver] Speed out of range: ", speed);
            return -1;
        }
        return setSpeedUnsafe(speed);
    }

    int stop() {
        LOG_DEBUG("[MotorDriver] Stopping motor");
        return setSpeedUnsafe(0);
    }

    MotorDriver(DRV8833 motor) : _motor(motor) {}

   private:
    DRV8833 _motor;

    int setSpeedUnsafe(int speed) {
        LOG_DEBUG("[MotorDriver] Setting speed to: ", speed);
        _motor.drive(speed, MOTOR_DRIVER_MAX_PWM, MOTOR_DRIVER_RAMP_TIME, MOTOR_DRIVER_BRAKE, MOTOR_DRIVER_NEUTRAL_BRAKE);
        return 0;
    }
};

#endif