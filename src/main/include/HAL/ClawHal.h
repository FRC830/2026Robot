#pragma once

#include <rev/SparkMax.h>
#include "CanConfig.h"

class Claw{

    public:

         Claw();
         ~Claw() = default;

        void ClawIntake(double dir);
        void RightIntake(int dir);
        void LeftIntake(int dir);

    private:
        rev::spark::SparkMax m_clawMotorA{CLAW_MOTOR_A_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_clawMotorB{CLAW_MOTOR_B_ID, rev::spark::SparkMax::MotorType::kBrushless};

        // speed
        double m_speed = 0.0;
        const double speed = 0.2;
};