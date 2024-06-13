/*
 * Copyright (c) 2022 Advanced Robotics at the University of Washington <robomstr@uw.edu>
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

#ifndef TAPROOT_MOVE_INTEGRAL_COMMAND_MOCK_HPP_
#define TAPROOT_MOVE_INTEGRAL_COMMAND_MOCK_HPP_

#include <gmock/gmock.h>

#include "tap/control/setpoint/commands/move_integral_command.hpp"

namespace tap::mock
{
class MoveIntegralCommandMock : public tap::control::setpoint::MoveIntegralCommand
{
public:
    static constexpr tap::control::setpoint::MoveIntegralCommand::Config DEFAULT_CONFIG = {1, 1, 1};

    MoveIntegralCommandMock(
        tap::control::setpoint::IntegrableSetpointSubsystem& integrableSetpointSubsystem,
        const tap::control::setpoint::MoveIntegralCommand::Config& config = DEFAULT_CONFIG);
    virtual ~MoveIntegralCommandMock();

    MOCK_METHOD(
        control::subsystem_scheduler_bitmap_t,
        getRequirementsBitwise,
        (),
        (const override));
    MOCK_METHOD(void, addSubsystemRequirement, (control::Subsystem*), (override));
    MOCK_METHOD(const char*, getName, (), (const override));
    MOCK_METHOD(bool, isReady, (), (override));
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(void, execute, (), (override));
    MOCK_METHOD(void, end, (bool interrupted), (override));
    MOCK_METHOD(bool, isFinished, (), (const override));
};
}  // namespace tap::mock

#endif  // TAPROOT_MOVE_INTEGRAL_COMMAND_MOCK_HPP_
