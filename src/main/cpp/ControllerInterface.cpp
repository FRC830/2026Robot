#include "ControllerInterface.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <string>

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData, bool auton)
{
    if (!auton)
    {
        UpdateStates(controlData);
        UpdateSwerveInput(controlData);
    }
    
    UpdatePigeonInput(controlData);
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

void ControllerInterface::UpdateStates(RobotControlData &controlData)
{
    
    if (m_copilot.GetRightBumperPressed()) // Passing
    {
        controlData.states.Passing = !controlData.states.Passing;
        controlData.states.Intaking = false; // Ensure Intaking is false when Launching is toggled
        controlData.states.Jam = false; // Ensure Jam is false when Launching is toggled
        controlData.states.Launching = false; // Ensure Launching is false when Passing is toggled
        controlData.states.Defense = false; // Ensure Defense is false when Intaking is toggled
        state = (controlData.states.Passing) ? "Passing" : "No State";
    } 
     else if (m_copilot.GetLeftBumperPressed()) // Launching
    {
        controlData.states.Launching = !controlData.states.Launching;
        controlData.states.Passing = false; // Ensure Passing is false when Launching is toggled
        controlData.states.Intaking = false; // Ensure Intaking is false when Launching is toggled
        controlData.states.Jam = false; // Ensure Jam is false when Launching is toggled
        controlData.states.Defense = false; // Ensure Defense is false when Intaking is toggled
        state = (controlData.states.Launching) ? "Launching" : "No State";
    }
     else if (m_copilot.GetBButtonPressed()) // Jam
    {
        controlData.states.Jam = !controlData.states.Jam;
        controlData.states.Passing = false; // Ensure Passing is false when Launching is toggled
        controlData.states.Intaking = false; // Ensure Intaking is false when Launching is toggled
        controlData.states.Launching = false; // Ensure Launching is false when Passing is toggled
        controlData.states.Defense = false; // Ensure Defense is false when Intaking is toggled
        state = (controlData.states.Jam) ? "Jam" : "No State";
        // controlData.intakeInput.shakeIntake = !controlData.intakeInput.shakeIntake;
        
    }
     else if (m_copilot.GetXButtonPressed()) // Intaking
    {
        controlData.states.Intaking = !controlData.states.Intaking;
        controlData.states.Passing = false; // Ensure Passing is false when Launching is toggled
        controlData.states.Jam = false; // Ensure Jam is false when Launching is toggled
        controlData.states.Launching = false; // Ensure Launching is false when Passing is toggled
        controlData.states.Defense = false; // Ensure Defense is false when Intaking is toggled
        state = (controlData.states.Intaking) ? "Intaking" : "No State";
    }
    else if (m_copilot.GetStartButtonPressed()) // Defense
    {
        controlData.states.Defense = !controlData.states.Defense;
        controlData.states.Passing = false; // Ensure Passing is false when Defense is toggled
        controlData.states.Intaking = false; // Ensure Intaking is false when Defense is toggled
        controlData.states.Jam = false; // Ensure Jam is false when Defense is toggled
        controlData.states.Launching = false; // Ensure Launching is false when Defense is toggled
        state = (controlData.states.Defense) ? "Defense" : "No State";
    }
    // controlData.states.Passing = false; // Ensure Passing is false when Launching is toggled
    // controlData.states.Intaking = false; // Ensure Intaking is false when Launching is toggled
    // controlData.states.Jam = false; // Ensure Jam is false when Launching is toggled
    // controlData.states.Launching = false; // Ensure Launching is false when Passing is toggled
    // controlData.states.Defense = false; // Ensure Defense is false when Intaking is toggled
    

    frc::SmartDashboard::PutString("Current State", state);

}

void ControllerInterface::UpdatePigeonInput(RobotControlData &controlData)
{
    controlData.resetPigeon.reset = m_pilot.GetStartButtonPressed();
}

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{  
    
    controlData.swerveInput.xTranslation = -m_pilot.GetLeftY() * 2;
    controlData.swerveInput.yTranslation = -m_pilot.GetLeftX() * 2;
    controlData.swerveInput.rotation = -m_pilot.GetRightX() * 2;    
}

void ControllerInterface::UpdateIntakeInput(RobotControlData &controlData)
{ 
    if (controlData.states.Passing || controlData.states.Launching || controlData.states.Intaking) // on if launching or passing or intaking
    {
        controlData.intakeInput.intakeState = false; //down
        controlData.intakeInput.intakeDirection = 1; //in
        controlData.intakeInput.shakeIntake = false;
    } else if (controlData.states.Jam || (m_copilot.GetRightY() < -0.1)) //jam or manual outtake
    {
        //controlData.intakeInput.intakeDirection = 1; //in
        controlData.intakeInput.shakeIntake = true;
    } else if (controlData.states.Defense) //Defense
    {
        controlData.intakeInput.intakeState = true; //up
        controlData.intakeInput.intakeDirection = 0; //stop
        controlData.intakeInput.shakeIntake = false;
    } else
    {
        controlData.intakeInput.intakeDirection = 0; //stop
        controlData.intakeInput.shakeIntake = false;
    }
    frc::SmartDashboard::PutBoolean("Intake state", controlData.intakeInput.intakeState);
    frc::SmartDashboard::PutNumber("Intake direction", controlData.intakeInput.intakeDirection);
}

#include <iostream>
void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData)
{ 
    controlData.launcherInput.autoAim = false;
    if (controlData.states.Launching)
    {
        controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
        controlData.launcherInput.indexerSpeeds = 0.8;
        controlData.launcherInput.autoAim = true;
    } else if (controlData.states.Passing)
    {
        controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
        controlData.launcherInput.indexerSpeeds = 0.8;
        controlData.launcherInput.autoAim = false;

        if(m_copilot.GetYButtonPressed()) // launcher RPM up
        {
            controlData.launcherInput.launcherRPM -= 100;
        }
        if(m_copilot.GetAButtonPressed()) // launch RPM down
        {
            controlData.launcherInput.launcherRPM += 100;
        }

    } else if (controlData.states.Jam)
    {
        controlData.launcherInput.disableLauncher = false; //enable launcher and set to default values
        controlData.launcherInput.launcherRPM = 750;
        controlData.launcherInput.indexerSpeeds = -0.333;
        controlData.launcherInput.autoAim = false;
    } else if (controlData.states.Intaking)
    {
        controlData.launcherInput.disableLauncher = true;
        // controlData.launcherInput.launcherRPM = 0;
        controlData.launcherInput.indexerSpeeds = -0.333;
        controlData.launcherInput.autoAim = false;
    } else {
        controlData.launcherInput.disableLauncher = true; //disable launcher
        controlData.launcherInput.indexerSpeeds = 0;
        // controlData.launcherInput.launcherRPM = 0;
        controlData.launcherInput.autoAim = false;
    }

    frc::SmartDashboard::PutNumber("Goal Launcher RPM", controlData.launcherInput.launcherRPM);
    frc::SmartDashboard::PutNumber("Indexer Speeds", controlData.launcherInput.indexerSpeeds);

}
void ControllerInterface::UpdateSpindexerInput(RobotControlData &controlData)
{
    if (controlData.states.Launching || controlData.states.Passing)
    {
        controlData.spindexerInput.enableSpindexer = true;
    } else
    {
        controlData.spindexerInput.enableSpindexer = false;
    }
    frc::SmartDashboard::PutBoolean("Spindexer Enabled", controlData.spindexerInput.enableSpindexer);
}


void ControllerInterface::VibrateController(double intensity, double duration)
{
    m_globalDuration = duration;
    m_timer.Restart();
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, intensity);
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, intensity);
}

void ControllerInterface::ResetState(RobotControlData &controlData)
{
    state = "Starting up";
    controlData.states.Launching = false;
    controlData.states.Passing = false;
    controlData.states.Intaking = false;
    controlData.states.Jam = false;
    controlData.states.Defense = false;
    controlData.intakeInput.shakeIntake = false;

}
