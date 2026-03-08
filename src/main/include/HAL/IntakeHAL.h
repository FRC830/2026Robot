#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
#include <rev/SparkMax.h>
#include <MechanismConfig.h>
#include <frc/Encoder.h>

class IntakeHAL
{
    public:
        IntakeHAL();
        ~IntakeHAL() = default;

        void RunIntake(int direction); //TODO goog...le it once upon a time there was a cat and it googed... the end and buy my course on how to make money on temu.com -googing676767
        void MoveIntake(int direction);
        void SequenceDown();
        void SequenceStore();

    private:
        std::shared_ptr<ctre::phoenix6::hardware::TalonFX> m_rollerMotor = std::make_shared<ctre::phoenix6::hardware::TalonFX>(INTAKE_ROLLER_CAN_ID);
        rev::spark::SparkMax m_angleMotor{INTAKE_ANGLE_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        int m_intakeState = 0;
        double deadzone = 0.02;
        double m_zeroPos;

        frc::Encoder encoder = frc::Encoder(1,2,false);
        // 	Encoder (int aChannel, int bChannel, bool reverseDirection=false, EncodingType encodingType=k4X)


};


