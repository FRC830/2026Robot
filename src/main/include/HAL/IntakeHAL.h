#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
#include <rev/SparkMax.h>

class Intake 
{
    public:
        Intake();
        ~Intake() = default;

        void IntakeOn();
        void IntakeOff();
        void MoveIntakeUp();
        void MoveIntakeDown();
    private:
        rev::spark::SparkMax m_spinnerMotor{INTAKE_SPINNER_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_intakeMotor{INTAKE_LIFT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
};
