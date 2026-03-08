
#include "ratpack/LinearActuator.h"
#include <rev/SparkMax.h>
#include <iostream>
#include <algorithm>

LinearActuator::LinearActuator() 
{
    //setbounds
}

void LinearActuator::setPosition(double pos)
{
    const double lower = 0.0;
    setPos = std::clamp(pos, lower, m_length);
    m_LinearActuator.SetSpeed(((setPos/m_length *2)-1));
 
}

void LinearActuator::updateCurPos(){
    double dt = m_timer.GetFPGATimestamp().value() - lastTime;
    if (curPos > setPos + m_speed *dt){
        curPos -= m_speed *dt;
    } else if(curPos < setPos - m_speed *dt){
        curPos += m_speed *dt;
    }else{
        curPos = setPos;
    }
 }

double LinearActuator::getPosition(){
    return curPos;
}

bool LinearActuator::isFinished(){
    return curPos == setPos;
}
