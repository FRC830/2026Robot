#include "ControllerInterface.h"
#include <iostream>

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{

    //UpdateSwerveInput(controlData);
    // UpdateNavxInput(controlData);
    UpdateLauncherInput(controlData);
    UpdateIntakeInput(controlData);
    // code for the VibrateController function
    // if (m_timer.Get().value()>=m_globalDuration)
    // {
    //     m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.0);
    //     m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
    // }
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

void ControllerInterface::UpdateIntakeInput(RobotControlData &controlData)
{ //used during intake, outtake, and passing states
    if (m_copilot.GetRightBumperPressed()) //passing
    {
        if (controlData.intakeInput.intakeState == true) //if the intake is currently up, then lower it and set to intake
        {
            controlData.intakeInput.intakeState = false; //down
            controlData.intakeInput.intakeDirection = -1; //in
        }
        else //if the intake is currently down, then raise it and stop the rollers
        {
            controlData.intakeInput.intakeState = true; //up
            controlData.intakeInput.intakeDirection = 0; //stop
        }

    }
    if(m_copilot.GetXButtonPressed())
    {
        if (controlData.intakeInput.intakeState == true) //if the intake is currently up, then lower it and set to intake
        {
            controlData.intakeInput.intakeState = false; //down
            controlData.intakeInput.intakeDirection = -1; //in
        }
        else //if the intake is currently down, then raise it and stop the rollers
        {
            controlData.intakeInput.intakeState = true; //up
            controlData.intakeInput.intakeDirection = 0; //stop
        }
    }
    else if (m_copilot.GetRightX() <-0.1) //manual outtake
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = 1; //out
    }
    else //neutral
    {
        controlData.intakeInput.intakeState = true; //up
        controlData.intakeInput.intakeDirection = 0; //stop
    }
    // else if (m_copilot.GetRightY() > 0.1) //outtake
    // {
    //     controlData.intakeInput.intakeState = false; //down
    //     controlData.intakeInput.intakeDirection = -1; //out
    // }
    // else if (m_copilot.GetRightY() < 0.1) //intake
    // {
    //     controlData.intakeInput.intakeState = false; //down
    //     controlData.intakeInput.intakeDirection = 1; //in
    // } else //neutral
    // {
    //     controlData.intakeInput.intakeState = true; //up
    //     controlData.intakeInput.intakeDirection = 0; //stop
    // }

}

#include <iostream>
void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{ //during passing and launching
    if(m_copilot.GetYButtonPressed()){
        controlData.launcherInput.launcherAngle = 144;
    }
    if(m_copilot.GetXButtonPressed()){
        controlData.launcherInput.launcherAngle = 36;
    }
    // if(m_copilot.GetBButtonPressed()){
    //     controlData.launcherInput.launcherRPM -= 100;
    // }
    // if(m_copilot.GetAButtonPressed()){
    //     controlData.launcherInput.launcherRPM += 100;
    // }
    if(m_copilot.GetLeftBumperButtonPressed()) //auto-aiming
    {
        controlData.launcherInput.autoAim = !controlData.launcherInput.autoAim; //toggle auto-aiming on and off
        // *** TEST CODE ***
        // if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
        // {
        //     controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
        //     controlData.launcherInput.launcherRPM = -6000;
        //     controlData.launcherInput.indexerSpeeds = -2000;
        //     std::cout << "Launcher Enabled" << std::endl;
        // }
        // else //if the launcher is currently enabled, disable it
        // {
        //     controlData.launcherInput.disableLauncher = true; //disable launcher
        //     controlData.launcherInput.indexerSpeeds = 0;
        //     std::cout << "Launcher Disabled" << std::endl;
        // }
    }
    
    else if (m_copilot.GetRightBumperPressed()) //passing
    {
        if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
        {
            controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
            controlData.launcherInput.launcherRPM = -6000;
            controlData.launcherInput.indexerSpeeds = -2000;
            std::cout << "Launcher Enabled" << std::endl;
        }
        else //if the launcher is currently enabled, disable it
        {
            controlData.launcherInput.disableLauncher = true; //disable launcher
            controlData.launcherInput.indexerSpeeds = 0;
            std::cout << "Launcher Disabled" << std::endl;
        }

    }
    
    else if (m_copilot.GetLeftX() > 0.1 || m_copilot.GetLeftX() < -0.1) //manual control of launcher RPM and indexer speeds using the left X axis
    {
        controlData.launcherInput.disableLauncher = false; //enable launcher
        controlData.launcherInput.launcherRPM = -(1+m_copilot.GetLeftX()) * 6000; //scale the left X axis to a range of 0 to -6000 RPM
        controlData.launcherInput.indexerSpeeds = -2000; //scale the left X axis to a range of 0 to -2000 RPM
    }
         
    else
    {
        controlData.launcherInput.disableLauncher = true; //disable launcher
        controlData.launcherInput.launcherRPM = 0; //if the left X axis is not being used, set the launcher RPM to 0
    }

}
void ControllerInterface::UpdateSpindexerInput(RobotControlData &controlData)
{
    if(m_copilot.GetBButtonPressed()){
        controlData.spindexerInput.enableSpindexer = !controlData.spindexerInput.enableSpindexer;  
    }
}


void ControllerInterface::VibrateController(double intensity, double duration)
{
    m_globalDuration = duration;
    m_timer.Restart();
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, intensity);
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, intensity);
}
