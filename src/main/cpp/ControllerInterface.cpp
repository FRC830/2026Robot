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
}
#include <iostream>

void ControllerInterface::UpdateIntakeInput(RobotControlData &controlData)
{ //used during intake, outtake, and passing states
    if (m_copilot.GetLeftTriggerAxis() > 0.1) //passing
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = 1; //in
    }
    else if (m_copilot.GetRightY() > 0.1) //outtake
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = -1; //out
    }
    else if (m_copilot.GetRightY() < 0.1) //intake
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = 1; //in
    } else //neutral
    {
        controlData.intakeInput.intakeState = true; //up
        controlData.intakeInput.intakeDirection = 0; //stop
    }

}
void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{ //during passing and launching
     if (m_copilot.GetLeftTriggerAxis() > 0.1) //passing
    {
        controlData.launcherInput.disableLauncher = false;
        controlData.launcherInput.launcherSpeed = 1000 + m_copilot.GetLeftY()*200;
    } else if (m_copilot.GetLeftY() > 0.1) //launching
    {
        controlData.launcherInput.disableLauncher = false;
        controlData.launcherInput.launcherSpeed = 1000 + m_copilot.GetLeftY()*200;
        if (m_copilot.GetAButton())
        {
            controlData.launcherInput.autoAim = true;
        }
        else
        {
            controlData.launcherInput.autoAim = false;
        }
    }
    else //neutral
    {
        controlData.launcherInput.disableLauncher = true;
        controlData.launcherInput.launcherSpeed = 0.0;
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
