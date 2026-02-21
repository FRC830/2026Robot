#include "HAL/LauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"
#include <math.h>

Launcher::Launcher()
{
    // Additional initialization if needed
    ctre::phoenix6::configs::TalonFXConfiguration flywheel_config{};

    ctre::phoenix6::configs::Slot0Configs &slot0Configs = flywheel_config.Slot0
        .WithKP(ratbot::LauncherConfig::Flywheel::P)
        .WithKI(ratbot::LauncherConfig::Flywheel::I)
        .WithKD(ratbot::LauncherConfig::Flywheel::D)
        .WithKG(ratbot::LauncherConfig::Flywheel::F);
    ctre::phoenix6::configs::MotorOutputConfigs &arm_output_config = flywheel_config.MotorOutput
        .WithInverted(ratbot::LauncherConfig::Flywheel::INVERTED)
        .WithNeutralMode(ratbot::LauncherConfig::Flywheel::IDLE_MODE);
    
    flywheel_config
        .WithSlot0(slot0Configs)
        .WithMotorOutput(arm_output_config);

}
void Launcher::SetLauncherSpeeds(double rightSpeed, double leftSpeed)
{
    m_desiredRightLauncherSpeed = rightSpeed;
    m_desiredLeftLauncherSpeed = leftSpeed;

    // Don't use PID to go to 0 to avoid stripping belts
    m_rightLauncher.SetControl(ctre::phoenix6::controls::VelocityDutyCycle(units::angular_velocity::turns_per_second_t(rightSpeed/60.0)));
    m_leftLauncher.SetControl(ctre::phoenix6::controls::VelocityDutyCycle(units::angular_velocity::turns_per_second_t(leftSpeed/60.0)));
}
void Launcher::SetIndexerSpeeds(double indexerSpeed)
{
    if (AreFlywheelsAtDesiredSpeed())
    {      
        m_Indexer->GetClosedLoopController().SetReference(indexerSpeed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    } else
    {
        m_Indexer->GetClosedLoopController().SetReference(0, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    }
}
double Launcher::GetRightLauncherRPM()
{
    return m_rightLauncher.GetVelocity().GetValueAsDouble() * 60.0;
}
double Launcher::GetLeftLauncherRPM()
{
    return m_leftLauncher.GetVelocity().GetValueAsDouble() * 60.0;
}


double Launcher::GetAngle()
{
    return m_verticalServo1.Get();
}
bool Launcher::AreFlywheelsAtDesiredSpeed()
{
    return ((std::fabs(GetRightLauncherRPM() - m_desiredRightLauncherSpeed)<=SMALL_NUM)&&(std::fabs(GetLeftLauncherRPM() - m_desiredLeftLauncherSpeed)<=SMALL_NUM));
}

void Launcher::SetAngle(double angle)
{
    m_verticalServo1.SetPosition(angle/180.0);
    m_verticalServo2.SetPosition(angle/180.0);
}

void Launcher::SetRPM(double wheel_rpm)
{
    double launcher_rpm = wheel_rpm/GEAR_RATIO;
    SetLauncherSpeeds(launcher_rpm, -launcher_rpm);
}