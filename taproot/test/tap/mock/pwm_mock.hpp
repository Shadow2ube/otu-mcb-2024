/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TAPROOT_PWM_MOCK_HPP_
#define TAPROOT_PWM_MOCK_HPP_

#include <gmock/gmock.h>

#include "tap/communication/gpio/pwm.hpp"

namespace tap
{
namespace mock
{
class PwmMock : public tap::gpio::Pwm
{
public:
    PwmMock();
    virtual ~PwmMock();

    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(void, writeAllZeros, (), (override));
    MOCK_METHOD(void, write, (float duty, tap::gpio::Pwm::Pin), (override));
    MOCK_METHOD(void, setTimerFrequency, (tap::gpio::Pwm::Timer, uint32_t), (override));
    MOCK_METHOD(void, pause, (tap::gpio::Pwm::Timer), (override));
    MOCK_METHOD(void, start, (tap::gpio::Pwm::Timer), (override));
};  // class PwmMock
}  // namespace mock
}  // namespace tap

#endif  //  TAPROOT_PWM_MOCK_HPP_
