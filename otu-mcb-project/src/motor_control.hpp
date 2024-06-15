#include <math.h>

#include <cstdint>

#include "tap/communication/serial/remote.hpp"
#include "tap/motor/dji_motor.hpp"

#include "global.hpp"

#define MAX_INT16 32676
#define MIN_INT16 -32676

using namespace tap::communication::serial;

float deg_to_rad(float deg) { return (deg * 3.14159262) / 180; }

int16_t map(int16_t in, int16_t min1, int16_t max1, int16_t min2, int16_t max2)
{
    // int m = (max2 - min2) / (max1 - min1);
    // int b = max1 - m * min1;
    // return m * in + b;
    return (max2 - min2) / (max1 - min1) * (in - min1) + max1;
}

void set_motor_speeds(const Remote &remote)
{
    /*
     * 1  4 +
     * 2  3 Y
     * X  +
     */
    // This is for the mouse movement of the turret
    int mouse_y = remote.getMouseX(),
        mouse_x = remote.getMouseY();
    
    float chassis_angle =
        deg_to_rad(tap::motor::DjiMotor::encoderToDegrees(pan_motor.getEncoderUnwrapped()));

    int16_t turret_pan =
        map(remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL), -1, 1, MIN_INT16, MAX_INT16) + mouse_x;

    int16_t turret_tilt =
        map(remote.getChannel(Remote::Channel::RIGHT_VERTICAL), -1, 1, MIN_INT16, MAX_INT16) + mouse_y;

    int16_t turret_x =
        map(remote.getChannel(Remote::Channel::LEFT_HORIZONTAL), -1, 1, MIN_INT16, MAX_INT16) +
        remote.keyPressed(Remote::Key::A) * MIN_INT16 +
        remote.keyPressed(Remote::Key::D) * MAX_INT16;

    int16_t turret_y =
        -map(remote.getChannel(Remote::Channel::LEFT_VERTICAL), -1, 1, MIN_INT16, MAX_INT16) +
        remote.keyPressed(Remote::Key::W) * MIN_INT16 +
        remote.keyPressed(Remote::Key::S) * MAX_INT16;

    int16_t chassis_x = turret_x * std::cos(chassis_angle) - turret_y * std::sin(chassis_angle);
    int16_t chassis_y = turret_x * std::sin(chassis_angle) + turret_y * std::cos(chassis_angle);

    // TODO: add rotation factor to make the robot rotate
    int c1 = (chassis_y + chassis_x);
    int c2 = (chassis_y - chassis_x);
    int c3 = -(chassis_y + chassis_x);
    int c4 = -(chassis_y - chassis_x);

    // lock the rotation of the chassis and turret
    // if (remote.getSwitch(Remote::Switch::RIGHT_SWITCH) == Remote::SwitchState::UP)
    // {
    //     c1 += turret_pan;
    //     c2 += turret_pan;
    //     c3 += turret_pan;
    //     c4 += turret_pan;
    // }
    // else
    {
        // TODO: subtract the rotation factor to make the  turret counter rotate
        pan_motor.setDesiredOutput(turret_pan);
    }

    tilt_motor.setDesiredOutput(turret_tilt);
    fl_motor.setDesiredOutput(c1);
    bl_motor.setDesiredOutput(c2);
    fr_motor.setDesiredOutput(c3);
    br_motor.setDesiredOutput(c4);

    // This is all for shooting the turret
    // if (remote.getMouseL() || remote.getSwitch())
    // {
        // agitator_motor.setDesiredOutput(MAX_INT16);
    // }
    // if (remote.getMouseR())
    // {
        // left_turret_motor.setDesiredOutput(MAX_INT16);
        // right_turret_motor.setDesiredOutput(MAX_INT16);
    // }
    left_turret_motor.setDesiredOutput(MAX_INT16);
    right_turret_motor.setDesiredOutput(-MAX_INT16);
    if (remote.getSwitch(Remote::Switch::RIGHT_SWITCH) == Remote::SwitchState::UP)
    {
        agitator_motor.setDesiredOutput(MAX_INT16);
    }
    // if (remote.getMouseR())
    // {
    //     left_turret_motor.setDesiredOutput(MAX_INT16);
    //     right_turret_motor.setDesiredOutput(MAX_INT16);
    // }
}
