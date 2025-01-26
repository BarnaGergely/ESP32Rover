#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <DRV8833.h>

#ifndef MOTOR_DRIVER_MAX_PWM
#define MOTOR_DRIVER_MAX_PWM 127
#endif

#ifndef MOTOR_DRIVER_MIN_PWM
#define MOTOR_DRIVER_MIN_PWM -128
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
    /// @param speed needs to bee between -100 and 100. Negative speed means
    /// rotating backwards, 0 is to stop.
    /// @return 0 if successfully set, -1 if the given speed is not between -100
    /// and 100 or if an error occurred
    int setSpeed(int speed) {
        if (speed < -100 || speed > 100) return -1;
        return setSpeedUnsafe(speed);
    }

    int stop() {
        _motor.drive(0, MOTOR_DRIVER_MAX_PWM, MOTOR_DRIVER_RAMP_TIME,
                     MOTOR_DRIVER_BRAKE, MOTOR_DRIVER_NEUTRAL_BRAKE);
        return 0;
    }

    MotorDriver(DRV8833 motor) : _motor(motor) {}

   private:
    DRV8833 _motor;

    int setSpeedUnsafe(int speed) {
        _motor.drive(speed, MOTOR_DRIVER_MAX_PWM, MOTOR_DRIVER_RAMP_TIME,
                     MOTOR_DRIVER_BRAKE, MOTOR_DRIVER_NEUTRAL_BRAKE);
        return 0;
    }
};

#endif