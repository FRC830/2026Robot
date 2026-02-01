#include "HAL/SpindexerHAL.h"

void Spindexer::RunSpindexer(double speed)
{
    m_SpindexerMotorA.Set(speed);
    m_SpindexerMotorB.Set(-speed);
}

double Spindexer::GetSpeed()
{
    return m_SpindexerMotorA.Get();
}

