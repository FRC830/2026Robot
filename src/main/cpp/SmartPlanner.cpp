#include "SmartPlanner.h"
#include <iostream>

SmartPlanner::SmartPlanner(PhotonVisionCamera &cam, WPISwerveDrive &swerve)
    : m_Cam(cam)
    , m_Swerve(swerve)
{}

void SmartPlanner::HandleInput(RobotControlData &data)
{
    if(data.plannerInput.Left_L1 || data.plannerInput.Left_L2 || data.plannerInput.Right_L1 || data.plannerInput.Right_L2)
    {
        SmartPlan(data);
    }
    else
    {
        m_state = 0;
        m_moveToPose.reset();
        m_pathstate = 0;
        //m_Swerve.SetFieldOriented();
    }
}

#include <iostream>
void SmartPlanner::SmartPlan(RobotControlData &data)
{

}

void SmartPlanner::followPath()
{
    switch(m_pathstate)
  {
    case 0:
      {
        m_path->get()->Initialize();
        m_pathstate++;
      }
      break;
    case 1:
      {
        m_path->get()->Execute();
        if (m_path->get()->IsFinished())
        {
          m_pathstate++;
        }
      }
      break;
    case 2:
      {
        m_path->get()->End(false);
        m_pathstate++;
      }
      break;
    case 3:
      {
        m_Swerve.Drive(0.0, 0.0, 0.0);
      }
    
      break;
    default:
      break;
  }
}
