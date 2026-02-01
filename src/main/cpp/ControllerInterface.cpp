#include "ControllerInterface.h"
#include <iostream>

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{

    UpdateSwerveInput(controlData);
    UpdateNavxInput(controlData);

    // code for the VibrateController function
    if (m_timer.Get().value()>=m_globalDuration)
    {
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.0);
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
    }
};



void ControllerInterface::UpdateNavxInput(RobotControlData &controlData)
{
    controlData.resetNavx.reset = m_pilot.GetStartButtonPressed();
}

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{  
    
    controlData.swerveInput.xTranslation = -m_pilot.GetLeftY();
    controlData.swerveInput.yTranslation = -m_pilot.GetLeftX();
    controlData.swerveInput.rotation = -m_pilot.GetRightX();

    if (m_pilot.GetAButton())
    {
        controlData.swerveInput.autoTarget = true;
    }
    else
    {
        controlData.swerveInput.autoTarget = false;
    }

    
}
#include <iostream>

void ControllerInterface::UpdateSmartplannerInput(RobotControlData &controlData)
{


}
void ControllerInterface::UpdateIntakeInput(RobotControlData &controlData)
{


}
void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{
     if (m_copilot.GetAButton())
    {
        controlData.launcherInput.disableLauncher = false;
        controlData.launcherInput.setLauncherToSpeed = true;
    }
    else
    {
        controlData.launcherInput.disableLauncher = true;
        controlData.launcherInput.setLauncherToSpeed = false;
    }
    

 
    controlData.launcherInput.indexerSpeeds = 1.0f;
}
void ControllerInterface::UpdateSpindexerInput(RobotControlData &controlData)
{

}

void ControllerInterface::VibrateController(double intensity, double duration)
{
    m_globalDuration = duration;
    m_timer.Restart();
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, intensity);
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, intensity);
}
