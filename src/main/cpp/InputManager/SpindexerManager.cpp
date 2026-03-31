#include "InputManager/SpindexerManager.h"

void SpindexerManager::ResetState(RobotControlData &robotControlData)
{
    robotControlData.spindexerOutput.RPM = 0;
}

void SpindexerManager::HandleInput(RobotControlData &robotControlData)
{
    if (robotControlData.spindexerInput.enableSpindexer && robotControlData.launcherOutput.launcherAtSpeed)
    {
        // switch (state) {
        //     case 0:
        //     {
        //         m_Timer.Reset();
        //         m_Timer.Start();
        //         state = 1;
        //         break;
        //     }
        //     case 1:
        //     {
                robotControlData.spindexerOutput.RPM = ratbot::Spindexer::DEFAULT_SPEED;
        //         if(m_Timer.Get() > (units::time::second_t) 5) {
        //             state = 2;
        //             break;
        //         }
        //     }
        //     case 2:
        //     {
        //         m_Timer.Reset();
        //         m_Timer.Start();
        //         state = 3;
        //         break;
        //     }
        //     case 3:
        //     {
        //         robotControlData.spindexerOutput.RPM = -ratbot::Spindexer::DEFAULT_SPEED;
        //         if(m_Timer.Get() > (units::time::second_t) 0.5) {
        //             state = 0;
        //             break;
        //         }
        //     }
        //     default: {
        //         break;
        //     }
        // }
    
        
    }  
    else
    {
        robotControlData.spindexerOutput.RPM = 0;
    }
    m_Spindexer.RunSpindexer(robotControlData.spindexerOutput.RPM);

}