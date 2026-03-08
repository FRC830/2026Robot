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
  auto camPose = m_Cam.GetPose();

  if (camPose.has_value())
  {
    auto poseThing = camPose;
    m_Swerve.UpdatePoseWithVision(poseThing->estimatedPose.ToPose2d(), units::time::second_t(poseThing->timestamp));
   // std::cout << camPose.value().estimatedPose.Rotation().Angle().value() * 180/3.14 << std::endl;
  }
  else
  {
    //std::cout << "no pose" << std::endl;
  }



  auto swervePose = m_Swerve.GetPose();
  double x = swervePose.X().value();
  double y = swervePose.Y().value();

  blueAlliance = frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kBlue;
  frc::SmartDashboard::PutNumber("X est pose", x);
  frc::SmartDashboard::PutNumber("Y est pose", y);
  if (blueAlliance)
  {
    m_targetAngle = atan2(4.035 - y,4.626 - x);
    targetPosition = frc::Translation2d(units::length::meter_t(4.035 - y), units::length::meter_t(4.626 - x));
    // targetPosition = frc::Translation2d( units::length::meter_t(4.626 - x),units::length::meter_t(4.035 - y));

  }
  else
  {
    m_targetAngle = atan2(4.035 - y, 11.915 - x);
    targetPosition= frc::Translation2d(units::length::meter_t(4.035 - y), units::length::meter_t(11.915 - x));
    // targetPosition= frc::Translation2d(units::length::meter_t(11.915 - x),units::length::meter_t(4.035 - y));
  }


  // find out which hub we target
  // 469.11, 158.84, red
  // 182.11, 158.84, blue


  double distance = targetPosition.Norm().value();
  double idealSpeed = 0;


  frc::Translation2d targetVector(units::meter_t (targetPosition.X().value()/distance * idealSpeed) , units::meter_t (targetPosition.Y().value()/distance * idealSpeed));
  
  double swerveX = m_Swerve.GetRobotRelativeSpeeds().vx();
  double swerveY = m_Swerve.GetRobotRelativeSpeeds().vy();

  // IMPORTANT DEBUG CODE
  // distance = 1.5;

  m_launchParam = m_launcherCalc.Calculate(distance, swervePose, swerveX, swerveY); //rpm
  data.launcherInput.launcherRPM = -m_launchParam.flywheelRPM;
  data.launcherInput.launcherAngle = m_launchParam.hoodAngle;
  data.launcherInput.indexerSpeeds = -0.8;
  // std::cout << "rpm " << data.launcherInput.launcherRPM << std::endl;
  // std::cout << "angle " << data.launcherInput.launcherAngle << std::endl;
  // std::cout << "ind speed " << data.launcherInput.indexerSpeeds << std::endl;
  // If a launcher was provided, command it from the planner (guarded)

  frc::SmartDashboard::PutNumber("target angle", (m_targetAngle * 180/3.1415));
  auto turnSpeed = m_moveToPose.angularRotation(m_Swerve.GetPose().Rotation().Degrees().value(),(m_targetAngle * 180/3.1415));

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
