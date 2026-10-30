#include "SmartPlanner.h"
#include <iostream>
#include <Robot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <PhotonVisionCamera.h>
#include <cmath>

SmartPlanner::SmartPlanner(PhotonVisionCamera &cam, WPISwerveDrive &swerve)
  : m_Cam(cam)
  , m_Swerve(swerve)
{}




void SmartPlanner::HandleInput(RobotControlData &data)
{
  SmartPlan(data);
    
}
#include <iostream>
void SmartPlanner::SmartPlan(RobotControlData &data)
{

  auto swervePose = m_Swerve.GetPose();
  double x = swervePose.X().value();
  double y = swervePose.Y().value();

  
  //    IMPORTANT: 

  //m_Swerve.Drive(        ,     ,    );

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
