// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <fmt/core.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include "MechanismConfig.h"
#include <frc/geometry/Pose2d.h>
#include <pathplanner/lib/auto/NamedCommands.h>
#include <wpinet/WebServer.h>
#include <frc/Filesystem.h>

Robot::Robot() {
  m_cam = std::make_shared<PhotonVisionCamera>("cam1", ratbot::VisionConfig::ROBOT_TO_CAMERA);

  m_smartPlanner = std::make_shared<SmartPlanner>(*m_cam, _swerve);
  
  m_autoChooser = pathplanner::AutoBuilder::buildAutoChooser();
  frc::SmartDashboard::PutData("Auto Chooser", &m_autoChooser);

  _swerve.SetShouldSwerveLock(true); 
}


void Robot::RobotPeriodic() {
  PrintSwerveInfo();
  m_cam->PrintVisionInfo();
  auto camPose = m_cam->GetPose();

  
  if (camPose.has_value())
  {
    auto poseThing = camPose;
    _swerve.UpdatePoseWithVision(poseThing->estimatedPose.ToPose2d(), units::time::second_t(poseThing->timestamp));
   // std::cout << camPose.value().estimatedPose.Rotation().Angle().value() * 180/3.14 << std::endl;
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() {

  switch(m_state)
  {
    case 0:
      {
        m_auto->Initialize();
        m_state++;
      }
      break;
    case 1:
      {
        m_auto->Execute();
        if (m_auto->IsFinished())
        {
          m_state++;
        }
      }
      break;
    case 2:
      {
        m_auto->End(false);
        m_state++;
      }
      break;
    case 3:
      {
        _swerve.Drive(0.0, 0.0, 0.0);
      }
    
      break;
    default:
      break;
  }

  TeleopPeriodic();

}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {


}

void Robot::TeleopPeriodic() {




}

void Robot::TeleopExit() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
