#pragma once

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;


};

struct ResetNavx
{
    bool reset;
};

struct SmartPlannerInput
{

};


struct RobotControlData {
    SwerveInput swerveInput;
    SmartPlannerInput plannerInput;
    ResetNavx resetNavx;
};


