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
  auto swervePose = m_Cam.GetPose();
  int x = swervePose->estimatedPose.X().value();
  int y = swervePose->estimatedPose.Y().value();
  blueAlliance = (std::hypot(11.915 - x, 4.035 - y) >= std::hypot(4.626 - x, 4.035 - y));
  frc::SmartDashboard::PutBoolean("Blue Alliance?", blueAlliance);
  if (swervePose->estimatedPose.X().value() != 0)
  {  
    frc::SmartDashboard::PutNumber("X est pose", x);
    frc::SmartDashboard::PutNumber("Y est pose", y);
    if (blueAlliance)
    {
      m_targetAngle = atan2(4.626 - x, 4.035 - y);
      distToHub = std::hypot(4.626 - x, 4.035 - y);
      targetPosition = frc::Translation2d(units::length::meter_t(4.626 - x), units::length::meter_t(4.035 - y));
    }
    else
    {
      m_targetAngle = atan2(11.915 - x, 4.035 - y);
      distToHub = std::hypot(11.915 - x, 4.035 - y);      
      targetPosition= frc::Translation2d(units::length::meter_t(11.915 - x), units::length::meter_t(4.035 - y));

    }
  }

  // find out which hub we target
  // 469.11, 158.84, red
  // 182.11, 158.84, blue


  double distance = targetPosition.Norm().value();
  //double idealSpeed = launcher.CalcSpeed(distance);


  frc::Translation2d targetVector(units::meter_t (targetPosition.X().value()/distance * 1) , units::meter_t (targetPosition.Y().value()/distance * 1));
  
  double swerveX = m_Swerve.GetRobotRelativeSpeeds().vx();
  double swerveY = m_Swerve.GetRobotRelativeSpeeds().vy();

  frc::Translation2d shotVector(units::meter_t (targetVector.X().value() - swerveX), units::meter_t (targetVector.X().value() - swerveY));
  //launcher spinning
  m_targetAngle = shotVector.Angle().Degrees().value();

  
  double speed = shotVector.Norm().value(); //mps
  //speed = launcher.CalcRPM(speed); //rpm
  //launcher.SetLauncherSpeeds(speed,speed);

  frc::SmartDashboard::PutNumber("target angle", (m_targetAngle * 180/3.1415)-90);


  auto turnSpeed = m_moveToPose.angularRotation(m_Swerve.GetPose().Rotation().Degrees().value(), (m_targetAngle * 180/3.1415)-90);
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
