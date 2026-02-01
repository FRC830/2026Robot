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

struct SpindexerData
{
    double RPM;
    double joystick;
};

struct RobotControlData {
    SwerveInput swerveInput;
    ResetNavx resetNavx;
    SpindexerData spindexer;
};


