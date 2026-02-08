#include "SmartPlanner.h"
#include <iostream>
#include <Robot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <PhotonVisionCamera.h>

SmartPlanner::SmartPlanner(PhotonVisionCamera &cam, WPISwerveDrive &swerve)
    : m_Cam(cam)
    , m_Swerve(swerve)
{}




void SmartPlanner::HandleInput(RobotControlData &data)
{

    
}

#include <iostream>
void SmartPlanner::SmartPlan(RobotControlData &data)
{
  auto swervePose = m_Cam.GetPose();

  if (swervePose->estimatedPose.X().value() != 0)
  {  
    frc::SmartDashboard::PutNumber("X est pose", 12.27-swervePose->estimatedPose.X().value()); //12.27-
    frc::SmartDashboard::PutNumber("Y est pose", 3.431-swervePose->estimatedPose.Y().value()); //3.431-
    m_targetAngle = atan2(3.431-swervePose->estimatedPose.Y().value(),12.27-swervePose->estimatedPose.X().value());
    frc::SmartDashboard::PutNumber("target angle", (m_targetAngle * 180/3.1415)-90);
  }
  auto turnSpeed = m_moveToPose.angularRotation(m_Swerve.GetPose().Rotation().Degrees().value(), (m_targetAngle * 180/3.1415));

  // find out which hub we target
  // 469.11, 158.84
  // 182.11, 158.84


  
  m_Swerve.Drive(data.swerveInput.xTranslation,data.swerveInput.yTranslation,turnSpeed);
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
