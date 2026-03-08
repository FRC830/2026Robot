#pragma once

#include "CanConfig.h"
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include "RobotControlData.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <MechanismConfig.h>

class Launcher
{
    public:
        Launcher();
        ~Launcher() = default; 
        void SetLauncherSpeeds(double rightSpeed, double leftSpeed);
        void SetIndexerSpeeds(double speed);
        double GetLeftLauncherRPM();
        double GetRightLauncherRPM();
        double GetAngle();
        bool AreFlywheelsAtDesiredSpeed();
        double CalcSpeed(double distance); // get mps by using distance v rpm and then rpm v speed
        double CalcRPM(double speed); // get rpm by using rpm v speed backwards
    private:
        rev::spark::SparkMax m_rightLauncher{LAUNCHER_FLYWHEEL_RIGHT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_leftLauncher{LAUNCHER_FLYWHEEL_LEFT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_Indexer{LAUNCHER_INDEXER_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        double m_desiredLeftIndexerSpeed;
        double m_desiredLeftLauncherSpeed; 
        double m_defaultIndexerSpeed = 0.8;
        
        double m_desiredRightIndexerSpeed;
        double m_desiredRightLauncherSpeed; 
        const double SMALL_NUM = 0.001; //change variable name accordingly; make a more suitable name                            
};