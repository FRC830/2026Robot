#include "HAL/SpindexerHAL.h"

void Spindexer::RunSpindexer(double speed)
{
    m_SpindexerMotorA.Set(speed);
}

double Spindexer::Get()
{
    return m_SpindexerMotorA.Get();
}

