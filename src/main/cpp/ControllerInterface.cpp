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
    if(m_copilot.GetRightBumperPressed() || m_copilot.GetLeftBumperPressed())//Launch or passing
    {
        if (controlData.intakeInput.intakeState == true) //if the intake is currently up, then lower it and set to intake
        {
            controlData.intakeInput.intakeState = false; //down
            controlData.intakeInput.intakeDirection = 1; //in
            m_statusIntake = true;
        }
        else //if the intake is currently down, then raise it and stop the rollers
        {
            //controlData.intakeInput.intakeState = true; //up
            controlData.intakeInput.intakeDirection = 0; //stop
            m_statusIntake = false;
        }
    }
    else if (m_copilot.GetBButtonPressed()) //jam button
    {
        if (controlData.intakeInput.intakeDirection == 1)
        {
            controlData.intakeInput.intakeDirection = -1;
        }else
        {
            controlData.intakeInput.intakeDirection = 1; //maybe change to 0
        }
        m_statusIntake = !m_statusIntake;
    }
    else if (m_copilot.GetRightX() < -0.1) //manual outtake
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = -1; //out
        m_statusIntake = false;
    }
    else if (m_copilot.GetStartButtonPressed()) //intake up
    {
        controlData.intakeInput.intakeState = true; //up
        controlData.intakeInput.intakeDirection = 0; //stop
        m_statusIntake = false;
    }
    else if (!m_statusIntake)
    {
        //controlData.intakeInput.intakeState = true; //up
        controlData.intakeInput.intakeDirection = 0; //stop
        m_statusIntake = false;
    }



}

#include <iostream>
void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{ 
    
    if (m_copilot.GetLeftBumperPressed()) //launch w/ auto-aiming
    {
        if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
        {
            controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
            controlData.launcherInput.launcherRPM = 3500;
            controlData.launcherInput.indexerSpeeds = -0.8;
            controlData.launcherInput.autoAim = true;
            m_statusLauncher=true;
            std::cout << "should be running" << std::endl;
        }
        else //if the launcher is currently enabled, disable it
        {
            controlData.launcherInput.disableLauncher = true; //disable launcher
            controlData.launcherInput.indexerSpeeds = 0;
            controlData.launcherInput.autoAim = false;
            m_statusLauncher=false;
        }

    } else if (m_copilot.GetRightBumperPressed()) //Passing w/out auto-aiming
    {
        if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
        {
            controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
            controlData.launcherInput.launcherRPM = 3500;
            controlData.launcherInput.indexerSpeeds = -0.8;
            controlData.launcherInput.autoAim = false;
            m_statusLauncher=true;
        }
        else //if the launcher is currently enabled, disable it
        {
            controlData.launcherInput.disableLauncher = true; //disable launcher
            controlData.launcherInput.indexerSpeeds = 0;
            controlData.launcherInput.autoAim = false;
            m_statusLauncher=false;
        }

    }
    else if (m_copilot.GetLeftX() > 0.1 || m_copilot.GetLeftX() < -0.1) //manual control of launcher RPM and indexer speeds using the left X axis
    {
        controlData.launcherInput.disableLauncher = false; //enable launcher
        controlData.launcherInput.launcherRPM = (1+m_copilot.GetLeftX()) * 300; //scale the left X axis to a range of 0 to 6000 RPM
        controlData.launcherInput.indexerSpeeds = -0.333; //scale the left X axis to a range of 0 to -2000 RPM
        
        m_statusLauncher = false;
    }
    else if (m_copilot.GetBButton()) //jam button
    {
         if (controlData.launcherInput.disableLauncher) //if the launcher is currently disabled, enable it and set to default values
        {
            controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
            controlData.launcherInput.launcherRPM = -750;
            controlData.launcherInput.indexerSpeeds = 0.333;
            controlData.launcherInput.autoAim = false;
            m_statusLauncher=true;
        }
        else //if the launcher is currently enabled, disable it
        {
            controlData.launcherInput.disableLauncher = true; //disable launcher
            controlData.launcherInput.indexerSpeeds = 0;
            controlData.launcherInput.autoAim = false;
            m_statusLauncher=false;
        }
    }
    else if (m_copilot.GetXButtonPressed()) //Intake
    {
        if (!m_statusLauncher) //intake run indexer wheels, but not intaking
        {
            m_statusLauncher = true;
            controlData.launcherInput.launcherRPM = 0;
            controlData.launcherInput.indexerSpeeds = 0.333;
        } else
         {
            m_statusLauncher = false;
            controlData.launcherInput.indexerSpeeds = 0;
        }
    }
    else if (!m_statusLauncher)
    {
        controlData.launcherInput.disableLauncher = true;
        controlData.launcherInput.launcherRPM = 0;
        controlData.launcherInput.indexerSpeeds = 0;
    }
    if(m_copilot.GetYButtonPressed()) //hood angle down
    {
        controlData.launcherInput.launcherAngle -= 10;
    }
    if(m_copilot.GetAButtonPressed()) //hood angle up
    {
        controlData.launcherInput.launcherAngle += 10;
    }
    frc::SmartDashboard::PutNumber("Goal Launcher RPM", controlData.launcherInput.launcherRPM);

}
void ControllerInterface::UpdateSpindexerInput(RobotControlData &controlData)
{
    if(m_copilot.GetLeftBumperPressed()) //launch w/ autoaimer
    {
        controlData.spindexerInput.enableSpindexer = !controlData.spindexerInput.enableSpindexer;
    } else if (m_copilot.GetRightBumperPressed()) //passing w/o autoaimer
    {
        controlData.spindexerInput.enableSpindexer = !controlData.spindexerInput.enableSpindexer;
    } else if (m_copilot.GetBButtonPressed()) //jam button
    {
        controlData.spindexerInput.enableSpindexer = false;
    } else if (m_copilot.GetXButtonPressed()) //intake
    {
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
