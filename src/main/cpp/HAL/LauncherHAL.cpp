#include "HAL/LauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"
#include <math.h>
#include <ctre/phoenix6/controls/VelocityVoltage.hpp>
#include <ctre/phoenix6/controls/Follower.hpp>
#include <units/voltage.h>
#include "ctre/phoenix6/configs/CurrentLimitsConfigs.hpp"



Launcher::Launcher()
{
    // Additional initialization if needed
    ctre::phoenix6::configs::TalonFXConfiguration flywheel_config{};

    ctre::phoenix6::configs::Slot0Configs &slot0Configs = flywheel_config.Slot0
        .WithKP(ratbot::LauncherConfig::Flywheel::P)
        .WithKI(ratbot::LauncherConfig::Flywheel::I)
        .WithKD(ratbot::LauncherConfig::Flywheel::D)
        .WithKV(ratbot::LauncherConfig::Flywheel::kVleft)
        .WithKA(ratbot::LauncherConfig::Flywheel::kA);
    ctre::phoenix6::configs::MotorOutputConfigs &flywheel_output_config = flywheel_config.MotorOutput
        .WithInverted(ratbot::LauncherConfig::Flywheel::INVERTED)
        .WithNeutralMode(ratbot::LauncherConfig::Flywheel::IDLE_MODE);

    ctre::phoenix6::configs::CurrentLimitsConfigs currentLimits{};
    currentLimits.StatorCurrentLimit = units::ampere_t{40.0}; // Set limit in Amperes
    currentLimits.StatorCurrentLimitEnable = true; // Enable the limit

    
    flywheel_config
        .WithSlot0(slot0Configs)
        .WithMotorOutput(flywheel_output_config);

    flywheel_config.CurrentLimits = currentLimits;

    
    ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
    for (int i = 0; i < 5; ++i) {
        status = m_leftLauncher->GetConfigurator().Apply(flywheel_config);
        if (status.IsOK()) break;
    }

        ctre::phoenix6::configs::TalonFXConfiguration flywheel_config2{};

    ctre::phoenix6::configs::Slot0Configs &slot0Configs2 = flywheel_config2.Slot0
        .WithKP(ratbot::LauncherConfig::Flywheel::P)
        .WithKI(ratbot::LauncherConfig::Flywheel::I)
        .WithKD(ratbot::LauncherConfig::Flywheel::D)
        .WithKV(ratbot::LauncherConfig::Flywheel::kVright)
        .WithKA(ratbot::LauncherConfig::Flywheel::kA);
    ctre::phoenix6::configs::MotorOutputConfigs &flywheel_output_config2 = flywheel_config2.MotorOutput
        .WithInverted(false)
        .WithNeutralMode(ratbot::LauncherConfig::Flywheel::IDLE_MODE);



    
    flywheel_config
        .WithSlot0(slot0Configs2)
        .WithMotorOutput(flywheel_output_config2);

    flywheel_config2.CurrentLimits = currentLimits;

    for (int i = 0; i < 5; ++i) {
        status = m_rightLauncher->GetConfigurator().Apply(flywheel_config2);
        if (status.IsOK()) break;

    }





}

#include <iostream>
void Launcher::SetLauncherSpeeds(double rightSpeed, double leftSpeed)
{

    m_desiredRightLauncherSpeed = rightSpeed;
    m_desiredLeftLauncherSpeed = leftSpeed;
    // std::cout << "desired " << m_desiredLeftLauncherSpeed << std::endl;
    if (rightSpeed == 0 &&
     leftSpeed == 0){
        m_rightLauncher->Set(0);
        
        m_leftLauncher->Set(0);
        return;
    } // Don't use PID to go to 0 to avoid stripping belts

    units::voltage::volt_t velocityFeedforward = units::voltage::volt_t(0.23);
    // m_leftLauncher->SetControl(ctre::phoenix6::controls::VelocityDutyCycle(units::angular_velocity::turns_per_second_t(leftSpeed/60.0)));
    m_leftLauncher->SetControl(ctre::phoenix6::controls::VelocityVoltage{(units::angular_velocity::turns_per_second_t (leftSpeed/60.0))}.WithFeedForward(velocityFeedforward));
    m_rightLauncher->SetControl(ctre::phoenix6::controls::VelocityVoltage{(units::angular_velocity::turns_per_second_t (rightSpeed/60.0))}.WithFeedForward(velocityFeedforward));

    // m_rightLauncher->Set(-1);
    // m_leftLauncher->Set(1);


}
void Launcher::SetIndexerSpeeds(double speed)
{
    // if (AreFlywheelsAtDesiredSpeed())

    // {     

    m_Indexer->Set(std::clamp(speed, -1.0, 1.0));


    // } else
    // {
    //     m_Indexer->GetClosedLoopController().SetReference(0, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    // }
}
double Launcher::GetRightLauncherRPM()
{
    return m_rightLauncher->GetVelocity().GetValueAsDouble() * 60.0;
}
double Launcher::GetLeftLauncherRPM()
{
    return m_leftLauncher->GetVelocity().GetValueAsDouble() * 60.0;
}


double Launcher::GetAngle()
{
    return m_verticalServo1.Get();
}
bool Launcher::AreFlywheelsAtDesiredSpeed()
{
    return ((std::fabs(std::fabs(GetLeftLauncherRPM()) - m_desiredLeftLauncherSpeed) <= 300));
}

void Launcher::SetAngle(double angle)
{
    // m_verticalServo1.SetPosition(angle/180);
} 

void Launcher::SetRPM(double wheel_rpm)
{
    double launcher_rpm = std::fabs(wheel_rpm);
    SetLauncherSpeeds(launcher_rpm, launcher_rpm);
}