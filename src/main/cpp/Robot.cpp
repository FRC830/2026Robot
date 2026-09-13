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


Robot::Robot() {

}


void Robot::RobotPeriodic() {
  
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() {


}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
  if ((m_controller.GetRightY() > 0.1) || (m_controller.GetRightY() < -0.1)) {
    m_Motor1.Set(m_controller.GetRightY() * 0.5);
  } else {
    m_Motor1.Set(0);
  }
  if ((m_controller.GetLeftY() > 0.1) || (m_controller.GetLeftY() < -0.1)) {
    m_Motor2.Set(m_controller.GetLeftY() * 0.75);
  } else {
    m_Motor2.Set(0);
  }
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
