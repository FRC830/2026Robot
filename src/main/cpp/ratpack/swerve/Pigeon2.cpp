#include "ratpack/swerve/Pigeon2.h"
#include <units/angle.h>

void Pigeon2::Configure(GyroConfig &config)
{
    ctre::phoenix6::hardware::Pigeon2 m_gyro{1, "rio"};
    m_is_inverted = config.is_inverted;
    m_zero_heading = config.zero_heading;
}

frc::Rotation3d Pigeon2::GetYawPitchRoll() 
{
    frc::Rotation3d yaw_pitch_roll = m_gyro->GetRotation3d();
    return yaw_pitch_roll;
}

frc::Rotation2d Pigeon2::GetHeading()
{
    frc::Rotation2d rawHeading = GetRawHeading();
    double heading = double((rawHeading - m_zero_heading).Degrees());

    if (heading < 0) 
    {
        heading += 360.0f;
    }

    return frc::Rotation2d(units::degree_t(heading));
}

frc::Rotation2d Pigeon2::GetRawHeading() 
{
    return m_gyro->GetRotation2d();
}

bool Pigeon2::GetInverted() 
{
    return m_is_inverted;
}

void Pigeon2::SetInverted(bool inverted) 
{
    m_is_inverted = inverted;
}

void Pigeon2::SetZeroHeading(double zero_heading) 
{
    m_zero_heading = frc::Rotation2d(units::degree_t(zero_heading));
}

void Pigeon2::Reset()
{
    m_gyro->Reset();
}
