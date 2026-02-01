#pragma once

#include "CanConfig.h"
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include "RobotControlData.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

class Spindexer
{
    public:
        Spindexer() = default;
        ~Spindexer() = default;

        void RunSpindexer(double speed, bool flywheelsAtSpeed);
        double GetSpeed();

    private:
        rev::spark::SparkMax m_SpindexerMotorA{SPINDEXER_A_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_SpindexerMotorB{SPINDEXER_B_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
};