
#pragma once
#include "Interfaces/SwerveGyro.h"
#include <studica/AHRS.h>
#include <frc/SPI.h>
#include <ctre/phoenix6/Pigeon2.hpp>

struct GyroConfig 
{
    bool is_inverted;
    frc::Rotation2d zero_heading;
};

class Pigeon2 : public SwerveGyro
{
    public:
        Pigeon2() = default;
        virtual ~Pigeon2() = default;
        virtual void Configure(GyroConfig &config) override;
        virtual frc::Rotation3d GetYawPitchRoll() override;
        virtual frc::Rotation2d GetHeading() override;
        virtual frc::Rotation2d GetRawHeading() override;
        virtual bool GetInverted() override;
        virtual void SetInverted(bool inverted) override;
        virtual void SetZeroHeading(double zero_heading) override;
        void Reset();
    private:
        bool m_is_inverted;
        frc::Rotation2d m_zero_heading; // Pigeon2 should set a zero heading during automatic calibration
        ctre::phoenix6::hardware::Pigeon2* m_gyro;
};