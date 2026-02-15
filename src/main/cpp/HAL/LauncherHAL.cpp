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


double Launcher::CalcRPM(double speed)
{
    // get rpm by using rpm v speed backwards
    return 1000;
}

double Launcher::CalcSpeed(double distance)
{
    // get mps by using distance v rpm and then rpm v speed
    return 1;
}