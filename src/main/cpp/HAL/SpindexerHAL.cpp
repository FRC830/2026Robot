#include "HAL/SpindexerHAL.h"

void Spindexer::RunSpindexer(double speed, bool flywheelsAtSpeed)
{
    if (flywheelsAtSpeed)
    {      
        m_SpindexerMotorA.Set(speed);
        m_SpindexerMotorB.Set(-speed);
    } else
    {
        m_SpindexerMotorA.Set(0);
        m_SpindexerMotorB.Set(-0);
    }
}

double Spindexer::GetSpeed()
{
    return m_SpindexerMotorA.Get();
}

