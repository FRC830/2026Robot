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
struct LauncherInput {
    double indexerSpeeds;
    bool setLauncherToSpeed;
    bool disableLauncher;
};
struct LauncherOutput{
    double leftSpeed;
    double rightSpeed;
    bool launcherAtSpeed;
};

struct SpindexerData
{
    double RPM;
    double joystick;
};

struct RobotControlData {
    SwerveInput swerveInput;
    ResetNavx resetNavx;
    LauncherInput launcherInput;
    LauncherOutput launcherOutput;
    SpindexerData spindexer;
};


