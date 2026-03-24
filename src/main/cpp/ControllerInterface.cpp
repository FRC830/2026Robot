#include "ControllerInterface.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{

    UpdateSwerveInput(controlData);
    // UpdateNavxInput(controlData);
    UpdateLauncherInput(controlData);
    UpdateIntakeInput(controlData);
    UpdateSpindexerInput(controlData);
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
    if(m_copilot.GetRightBumperPressed())// instake
    {
        if (controlData.intakeInput.intakeState == true) //if the intake is currently up, then lower it and set to intake
        {
            controlData.intakeInput.intakeState = false; //down
            controlData.intakeInput.intakeDirection = 1; //in
            m_statusIntake = true;
        }
        else //if the intake is currently down, then raise it and stop the rollers
        {
            controlData.intakeInput.intakeState = true; //up
            controlData.intakeInput.intakeDirection = 0; //stop
            m_statusIntake = false;
        }
    }
    else if (m_copilot.GetRightX() <-0.1) //manual outtake
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = -1; //out
        m_statusIntake = false;
    }
    else if (!m_statusIntake)
    {
        controlData.intakeInput.intakeState = true; //up
        controlData.intakeInput.intakeDirection = 0; //stop
        m_statusIntake = false;
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
    
    // if(m_copilot.GetYButtonPressed()){
    //     controlData.launcherInput.launcherAngle += 10;
    // }
    // if(m_copilot.GetXButtonPressed()){
    //     controlData.launcherInput.launcherAngle -= 10;
    // }
    // *** DEBUG CODE ***
    if(m_copilot.GetYButtonPressed()){
        controlData.launcherInput.launcherRPM -= 100;
    }
    if(m_copilot.GetAButtonPressed()){
        controlData.launcherInput.launcherRPM += 100;
    }
    // if(m_copilot.GetLeftBumperButtonPressed()) //auto-aiming
    // {
    //     controlData.launcherInput.autoAim = !controlData.launcherInput.autoAim; //toggle auto-aiming on and off
    //     // *** TEST CODE ***
    //     // if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
    //     // {
    //     //     controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
    //     //     controlData.launcherInput.launcherRPM = -6000;
    //     //     controlData.launcherInput.indexerSpeeds = -2000;
    //     //     std::cout << "Launcher Enabled" << std::endl;
    //     // }
    //     // else //if the launcher is currently enabled, disable it
    //     // {
    //     //     controlData.launcherInput.disableLauncher = true; //disable launcher
    //     //     controlData.launcherInput.indexerSpeeds = 0;
    //     //     std::cout << "Launcher Disabled" << std::endl;
    //     // }
    // }
    
    if (m_copilot.GetLeftBumperPressed()) //launch
    {
        if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
        {
            controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
            controlData.launcherInput.launcherRPM = -1000;
            controlData.launcherInput.indexerSpeeds = 0.5;
            std::cout << "Launcher Enabled" << std::endl;
           
            m_statusLauncher=true;
        }
        else //if the launcher is currently enabled, disable it
        {
            controlData.launcherInput.disableLauncher = true; //disable launcher
            controlData.launcherInput.indexerSpeeds = 0;
            std::cout << "Launcher Disabled" << std::endl;
            m_statusLauncher=false;
        }

    }

    

    frc::SmartDashboard::PutNumber("Goal Launcher RPM", controlData.launcherInput.launcherRPM);

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
