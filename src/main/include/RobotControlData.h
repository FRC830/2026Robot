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
    double launcherSpeed;
    bool disableLauncher;
    bool autoAim;
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

struct IntakeInput
{
    bool intakeState; //true means up
    int intakeDirection; //1 is in, -1 is out, 0 is stop
};

struct States
{
    bool Launching;
    bool Passing;
    bool Intaking;
    bool Jam;
    bool Defense;
};

struct RobotControlData {
    SwerveInput swerveInput;
    ResetNavx resetNavx;
    LauncherInput launcherInput;
    LauncherOutput launcherOutput;
    SpindexerData spindexer;
    IntakeInput intakeInput;
    States states;
};


