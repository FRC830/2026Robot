#include "MoveToPose.h"
#include "MechanismConfig.h"

// TODO: look at these files to understand how to setup and use a trapezoid move using switch statements
        // - https://github.com/FRC830/2024Robot/blob/master/src/main/include/subsystems/IntakeHAL.h (trapezoid move member variable init)
       //  - https://github.com/FRC830/2024Robot/blob/master/src/main/cpp/subsystems/IntakeHAL.cpp (ProfiledMoveToAngle function)
// TODO: don't worry about doing anything with the drive base for now

frc::ChassisSpeeds MoveToPose::move(
    frc::Pose2d current,
    frc::Pose2d desired
) {
    m_current = current;

    auto omega = angularRotation(
        current.Rotation().Degrees().value(),
        desired.Rotation().Degrees().value()
    );

    auto translation = linearTranslation(desired);

    return frc::ChassisSpeeds{
        translation.first,
        translation.second,
        omega
    };
}


// #include <iostream>


units::degrees_per_second_t MoveToPose::angularRotation(
    double currentDeg,
    double desiredDeg
) {
    double omega = m_thetaPID.Calculate(currentDeg, desiredDeg);

    // Clamp to max angular speed
    omega = std::clamp(
        omega,
        -ratbot::MoveToPoseConfig::MAX_TURN_SPEED_DEG_PER_SEC,
         ratbot::MoveToPoseConfig::MAX_TURN_SPEED_DEG_PER_SEC
    );

    if (m_thetaPID.AtSetpoint()) {
        omega = 0.0;
        m_MoveAngleToState = 3;
    }

    return units::degrees_per_second_t{omega};
}


std::pair<units::feet_per_second_t, units::feet_per_second_t>
MoveToPose::linearTranslation(frc::Pose2d desired) {

    double vx = m_xPID.Calculate(
        m_current.X().value(),
        desired.X().value()
    );

    double vy = m_yPID.Calculate(
        m_current.Y().value(),
        desired.Y().value()
    );

    // Clamp speeds
    vx = std::clamp(
        vx,
        -ratbot::MoveToPoseConfig::MAX_SPEED_M_PER_SEC,
         ratbot::MoveToPoseConfig::MAX_SPEED_M_PER_SEC
    );

    vy = std::clamp(
        vy,
        -ratbot::MoveToPoseConfig::MAX_SPEED_M_PER_SEC,
         ratbot::MoveToPoseConfig::MAX_SPEED_M_PER_SEC
    );

    if (m_xPID.AtSetpoint() && m_yPID.AtSetpoint()) {
        vx = 0.0;
        vy = 0.0;
        m_MoveTranslationToState = 3;
    }

    return {
        units::meters_per_second_t{vx},
        units::meters_per_second_t{vy}
    };
}


void MoveToPose::reset()
{

    m_MoveAngleToState = 0;
    m_MoveTranslationToState = 0;
    m_MoveToState = 0;
     m_thetaPID.EnableContinuousInput(-180.0, 180.0);
    m_thetaPID.SetTolerance(kThetaTolerance.value());

    m_xPID.SetTolerance(kPosTolerance.value());
    m_yPID.SetTolerance(kPosTolerance.value());

    
}

bool MoveToPose::isDone() {
    return m_thetaPID.AtSetpoint()
        && m_xPID.AtSetpoint()
        && m_yPID.AtSetpoint();
}


bool MoveToPose::turnIsDone()
{
    return m_MoveAngleToState == 3;
}
