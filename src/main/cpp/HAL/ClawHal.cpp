#include "HAL/ClawHal.h"

Claw::Claw()
{


}

void Claw::ClawIntake(double dir){

    m_clawMotorA.Set(-dir*speed);
    m_clawMotorB.Set(dir*speed);
}
void Claw::RightIntake(int dir){
    m_clawMotorA.Set(-dir*speed);
}
void Claw::LeftIntake(int dir){
    m_clawMotorB.Set(dir*speed);
}