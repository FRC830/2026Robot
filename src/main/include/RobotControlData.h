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
    double launcherRPM;
    double launcherAngle;
    bool disableLauncher;
    bool autoAim;
};

struct LauncherOutput{
    double leftLauncherRPM;
    double rightLauncherRPM;
    double launcherAngle;
    bool launcherAtSpeed;
};

struct SpindexerData
{
    double RPM;
    double joystick;
};

struct IntakeInput
{
    bool intakeState; //true means up
    int intakeDirection; //1 is in, -1 is out, 0 is stop
};

struct RobotControlData {
    SwerveInput swerveInput;
    ResetNavx resetNavx;
    LauncherInput launcherInput;
    LauncherOutput launcherOutput;
    SpindexerData spindexer;
    IntakeInput intakeInput;
};


