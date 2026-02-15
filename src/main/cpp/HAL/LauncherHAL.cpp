#include "HAL/LauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

Launcher::Launcher()
{

}
void Launcher::SetLauncherSpeeds(double rightSpeed, double leftSpeed)
{
    m_desiredRightLauncherSpeed = rightSpeed;
    m_desiredLeftLauncherSpeed = leftSpeed;

    // Don't use PID to go to 0 to avoid stripping belts
    auto rightControlType = (std::fabs(rightSpeed) <= 1.0f) ? rev::spark::SparkLowLevel::ControlType::kDutyCycle : rev::spark::SparkLowLevel::ControlType::kVelocity;
    auto leftControlType = (std::fabs(leftSpeed) <= 1.0f) ? rev::spark::SparkLowLevel::ControlType::kDutyCycle : rev::spark::SparkLowLevel::ControlType::kVelocity;

    m_rightLauncher.GetClosedLoopController().SetReference(rightSpeed, rightControlType);
    m_leftLauncher.GetClosedLoopController().SetReference(leftSpeed, leftControlType);
}
void Launcher::SetIndexerSpeeds(double indexerSpeed)
{
    if (AreFlywheelsAtDesiredSpeed())
    {      
        m_leftIndexer.GetClosedLoopController().SetReference(indexerSpeed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
        m_rightIndexer.GetClosedLoopController().SetReference(indexerSpeed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    } else
    {
        m_leftIndexer.GetClosedLoopController().SetReference(0, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
        m_rightIndexer.GetClosedLoopController().SetReference(0, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    }
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
    return ((std::fabs(GetRightLauncherSpeed() - m_desiredRightLauncherSpeed)<=SMALL_NUM)&&(std::fabs(GetLeftLauncherSpeed() - m_desiredLeftLauncherSpeed)<=SMALL_NUM));
}

void Launcher::SetAngle(double angle)
{
    m_verticalServo1.Set(angle*63);
    m_verticalServo2.Set(angle*63);

}

void Launcher::SetRPM(double wheel_rpm)
{
    double launcher_rpm = wheel_rpm/GEAR_RATIO;
    SetLauncherSpeeds(launcher_rpm, -launcher_rpm);
}