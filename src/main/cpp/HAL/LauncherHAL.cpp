#include "HAL/LauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

Launcher::Launcher()
{
    // Additional initialization if needed
    ctre::phoenix6::configs::TalonFXConfiguration flywheel_config{};

    ctre::phoenix6::configs::Slot0Configs &slot0Configs = flywheel_config.Slot0
        .WithKP(ratbot::LauncherConfig::Flywheel::P)
        .WithKI(ratbot::LauncherConfig::Flywheel::I)
        .WithKD(ratbot::LauncherConfig::Flywheel::D)
        .WithKV(ratbot::LauncherConfig::Flywheel::kV)
        .WithKA(ratbot::LauncherConfig::Flywheel::kA);
    ctre::phoenix6::configs::MotorOutputConfigs &arm_output_config = flywheel_config.MotorOutput
        .WithInverted(ratbot::LauncherConfig::Flywheel::INVERTED)
        .WithNeutralMode(ratbot::LauncherConfig::Flywheel::IDLE_MODE);
    
    flywheel_config
        .WithSlot0(slot0Configs)
        .WithMotorOutput(arm_output_config);
    
    
    ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
    for (int i = 0; i < 5; ++i) {
        status = m_leftLauncher->GetConfigurator().Apply(flywheel_config);
        if (status.IsOK()) break;
    }
    m_rightLauncher->GetConfigurator().Apply(flywheel_config);



}
void Launcher::SetLauncherSpeeds(double rightSpeed, double leftSpeed)
{
    m_desiredRightLauncherSpeed = rightSpeed;
    m_desiredLeftLauncherSpeed = leftSpeed;
    if (rightSpeed == 0 && leftSpeed == 0){
        m_rightLauncher->Set(0);
        m_leftLauncher->Set(0);
        return;
    } // Don't use PID to go to 0 to avoid stripping belts
    m_leftLauncher->SetControl(ctre::phoenix6::controls::VelocityDutyCycle(units::angular_velocity::turns_per_second_t(leftSpeed/60.0)));
    m_rightLauncher->SetControl(ctre::phoenix6::controls::Follower{m_leftLauncher->GetDeviceID(), ctre::phoenix6::signals::MotorAlignmentValue::Opposed});

    
    // m_rightLauncher->Set(-1);
    // m_leftLauncher->Set(1);


    m_rightLauncher.GetClosedLoopController().SetReference(rightSpeed, rightControlType);
    m_leftLauncher.GetClosedLoopController().SetReference(leftSpeed, leftControlType);
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
double Launcher::GetRightLauncherSpeed()
{
    return m_rightLauncher.GetEncoder().GetVelocity();
}
double Launcher::GetLeftLauncherSpeed()
{
    return m_leftLauncher.GetEncoder().GetVelocity();
}
bool Launcher::AreFlywheelsAtDesiredSpeed()
{
    return ((std::fabs(std::fabs(GetRightLauncherRPM()) - m_desiredRightLauncherSpeed)<=SMALL_NUM)&&(std::fabs(std::fabs(GetLeftLauncherRPM()) - m_desiredLeftLauncherSpeed)<=SMALL_NUM));
}


double Launcher::CalcRPM(double speed)
{
    // get rpm by using rpm v speed backwards
    return 1000;
}

double Launcher::CalcSpeed(double distance)
{
    double launcher_rpm = std::fabs(wheel_rpm);
    SetLauncherSpeeds(launcher_rpm, launcher_rpm);
}