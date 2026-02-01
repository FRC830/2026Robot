#include "HAL/SpindexerHAL.h"

void Spindexer::RunSpindexer(double speed, bool flywheelsAtSpeed)
{
    if (flywheelsAtSpeed)
    {      
        m_SpindexerMotorA.GetClosedLoopController().SetReference(speed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
        m_SpindexerMotorB.GetClosedLoopController().SetReference(-speed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    } else
    {
        m_SpindexerMotorA.GetClosedLoopController().SetReference(0, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
        m_SpindexerMotorB.GetClosedLoopController().SetReference(0, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    }
}

double Spindexer::GetSpeed()
{
    return m_SpindexerMotorA.Get();
}

