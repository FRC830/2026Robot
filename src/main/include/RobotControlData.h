#pragma once

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;

    bool autoTarget;
    bool goFieldOriented;
};

struct ResetNavx
{
    bool reset;
};

struct IntakeInput{
    bool intakeDirection; 
    bool intakeState;
};

struct RobotControlData {
    SwerveInput swerveInput;
    ResetNavx resetNavx;
    IntakeInput intakeInput;
};


