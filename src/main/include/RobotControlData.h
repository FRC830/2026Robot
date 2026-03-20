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

struct SpindexerInput
{
    bool enableSpindexer;
};

struct SpindexerOutput
{
    double RPM;
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
    SpindexerInput spindexerInput;
    SpindexerOutput spindexerOutput;
    IntakeInput intakeInput;
    States states;
};


