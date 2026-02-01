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

struct RobotControlData {
    SwerveInput swerveInput;
    ResetNavx resetNavx;
};


