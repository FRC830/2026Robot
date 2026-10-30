#pragma once

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;

    bool autoTarget;
    bool goFieldOriented;
};

struct ResetPigeon
{
    bool reset;
};


struct RobotControlData
{
    SwerveInput swerveInput;
    ResetPigeon resetPigeon;
};