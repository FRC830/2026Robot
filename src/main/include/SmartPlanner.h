#pragma once

#include "MoveToPose.h"
#include "PhotonVisionCamera.h"
#include "ratpack/swerve/WPISwerveDrive.h"
#include "RobotControlData.h"
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include "ScoringPositionMap.h"
#include <units/length.h>
#include <units/angular_velocity.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <memory>
#include <HAL/LauncherHAL.h>
#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Rotation2d.h>
#include "InputManager/LauncherManager.h"


class SmartPlanner{
    public:
        SmartPlanner(PhotonVisionCamera &cam, WPISwerveDrive &swerve);
        ~SmartPlanner() = default;

        void HandleInput(RobotControlData &data);

    private:
        SmartPlanner() = default;
        void SmartPlan(RobotControlData &data);

        void followPath();
        pathplanner::PathConstraints m_constraints = pathplanner::PathConstraints{1.0_mps, 1.0_mps_sq, 1.6_rad_per_s, units::radians_per_second_squared_t{0.8}};
        std::unique_ptr<frc2::CommandPtr> m_path;
        PhotonVisionCamera &m_Cam;
        MoveToPose m_moveToPose;
        WPISwerveDrive &m_Swerve;
        int m_pathstate;
        int m_state;
        frc::Pose2d m_targetPose;
        frc::Pose2d m_startPose;
        double m_targetAngle = 0;
        int m_tagId;
        bool blueAlliance;
        double distToHub = 0;
        frc::Translation2d targetPosition;

       // LauncherManager launcherManager;
        

        ScoringPositionMap m_positionMap;
};