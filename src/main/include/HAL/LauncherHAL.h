#pragma once

#include "CanConfig.h"
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include "RobotControlData.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <MechanismConfig.h>
#include <frc/Servo.h>
#include <memory.h>

class Launcher
{
    public:
        Launcher();
        ~Launcher() = default; 
        void SetLauncherSpeeds(double rightSpeed, double leftSpeed);
        void SetIndexerSpeeds(double indexerSpeed);
        double GetLeftLauncherRPM();
        double GetRightLauncherRPM();
        double GetAngle();
        bool AreFlywheelsAtDesiredSpeed();
        void SetAngle(double angle);
        void SetRPM(double rpm);

    private:
        std::shared_ptr<rev::spark::SparkMax> m_leftIndexer = std::make_shared<rev::spark::SparkMax>(LAUNCHER_INDEXER_RIGHT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless);
        std::shared_ptr<rev::spark::SparkMax> m_rightIndexer = std::make_shared<rev::spark::SparkMax>(LAUNCHER_INDEXER_LEFT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless);
        std::shared_ptr<rev::spark::SparkMax> m_rightLauncher = std::make_shared<rev::spark::SparkMax>(LAUNCHER_FLYWHEEL_RIGHT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless);
        std::shared_ptr<rev::spark::SparkMax> m_leftLauncher = std::make_shared<rev::spark::SparkMax>(LAUNCHER_FLYWHEEL_LEFT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless);

        
        frc::Servo m_verticalServo1{SERVO_ID1};
        frc::Servo m_verticalServo2{SERVO_ID2};
    


        double m_desiredLeftIndexerSpeed;
        double m_desiredLeftLauncherSpeed; 
        double m_desiredRightIndexerSpeed;
        double m_desiredRightLauncherSpeed; 
        const double GEAR_RATIO = 2; // placeholder
        const double SMALL_NUM = 0.001; //change variable name accordingly; make a more suitable name                            
};