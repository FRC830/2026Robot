// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <optional> 

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <frc/Timer.h>

#include "ratpack/swerve/AnalogAbsoluteEncoder.h"
#include "ratpack/swerve/Pigeon2.h"
#include "ratpack/swerve/NeoDriveMotor.h"
#include "ratpack/swerve/NeoTurnMotor.h"
#include "ratpack/swerve/WPISwerveModule.h"
#include "ratpack/swerve/WPISwerveDrive.h"

#include "PhotonVisionCamera.h"
#include "ControllerInterface.h"
#include "RobotControlData.h"
#include "MoveToPose.h"
#include "SmartPlanner.h"
#include "ratpack/swerve/SwerveConfig.h"


class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void DisabledExit() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void AutonomousExit() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TeleopExit() override;
  void TestInit() override;
  void TestPeriodic() override;
  void TestExit() override;
  void SwerveInit();
  void PrintSwerveInfo();

 private:

};
