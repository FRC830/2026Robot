#pragma once

#include <rev/config/SparkMaxConfig.h>
#include "PhotonVisionCamera.h"
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configuration.hpp>
#include <ctre/phoenix6/configs/Configurator.hpp>
#include <frc/geometry/Transform3d.h>
#include <frc/geometry/Translation3d.h>

namespace ratbot
{

    const double VOLTAGE_COMPENSATION = 10.5f;
    namespace VisionConfig
    {
        constexpr frc::Transform3d ROBOT_TO_CAMERA = frc::Transform3d{frc::Translation3d(14_in, -4_in, 0_in), frc::Rotation3d(0_rad, 0_rad, 0_rad)};
    }
    namespace MoveToPoseConfig
    {
        // TODO: tune values on carpet
        const double MAX_TURN_SPEED_DEG_PER_SEC = 720.0f;
        const double TURN_FEED_FORWARD_DEG_PER_SEC = 20.0f;
        const double MAX_SPEED_M_PER_SEC = 1.32f; // todo: change!!!
        const double SPEED_FEED_FORWARD_M_PER_SEC = 0.1f; //todo: change!!!!!
    }
    namespace Intake
    {
        const double INTAKE_ROLLER_SPEED = 0.8;
        const double INTAKE_ANGLE_SPEED = 0.1;
        const double DOWN_LOCATION = 0;
    }
    namespace LauncherConfig
    {
        namespace Flywheel
        {
            const double P = 0.00025;
            const double I = 0.0;
            const double D = 0.35;
            const double F = 0.0;
            const double VEL_CONV_FACTOR = 1.0;
            const double CURRENT_LIM = 30.0;
            const bool INVERTED = true;
            constexpr rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        }

        namespace Indexer
        {
            const double CURRENT_LIM = 20.0;
            const bool INVERTED = true;
            constexpr rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        } 
    }
    namespace Spindexer
    {
        const double DEFAULT_SPEED = 0.8;
    }

}