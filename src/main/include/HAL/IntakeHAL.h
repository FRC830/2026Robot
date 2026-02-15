#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
#include <rev/SparkMax.h>
#include <MechanismConfig.h>
#include <frc/controller/PIDController.h>

class IntakeHAL
{
    public:
        IntakeHAL();
        ~IntakeHAL() = default;

        void RunIntake(int direction); //goog...le it once upon a time there was a cat and it googed... the end and buy my course on how to make money on temu.com -googing676767
        void MoveIntake(double setpoint);
        void SequenceDown();
        void SequenceStore();
        void ResetPID();

    private:
        rev::spark::SparkMax m_rollerMotor{INTAKE_ROLLER_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_angleMotor{INTAKE_ANGLE_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        int m_intakeState = 0;
        double deadzone = 0.02;

        frc::PIDController m_thetaPID{1, 0.0, 0.001};   // pleasse dont break :pray: goog...:goog: :pray:
        
};
