#pragma once
#include "Interfaces/SwerveDrive.h"
#include "Interfaces/SwerveModule.h"
#include "Interfaces/SwerveGyro.h"
#include "frc/estimator/SwerveDrivePoseEstimator.h"
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <array>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Pose3d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/DriverStation.h>
#include <utility>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <pathplanner/lib/controllers/PPHolonomicDriveController.h>
#include <pathplanner/lib/config/PIDConstants.h>
#include <pathplanner/lib/controllers/PathFollowingController.h>
#include <frc/AnalogEncoder.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <ctre/phoenix6/CANcoder.hpp>
#include "rev/SparkMax.h"
#include <units/length.h>

struct SwerveConfig{
    bool idle_mode;
    bool ebrake;
    bool orientation;
    double maxDriveSpeed;
    double maxTurnSpeed;
    double deadzone;
    SwerveGyro *gyro;
    // Location of motors relative to the center of the robot
    frc::Translation2d frontLeftLocation;
    frc::Translation2d frontRightLocation;
    frc::Translation2d backLeftLocation;
    frc::Translation2d backRightLocation;
    //std::array<SwerveModule, 4>& modules;
};

class WPISwerveDrive : public SwerveDrive
{
    public:
        WPISwerveDrive() = default;
        virtual ~WPISwerveDrive() = default;
        virtual void Configure(SwerveConfig &config) override;
        virtual bool GetEbrake() override;
        virtual void SetEbrake(bool ebrake) override;
        virtual void Drive(double x_position, double y_position, double rotation);
        void Drive(double x_position, double y_position, units::degrees_per_second_t omega);
        virtual void Drive(units::feet_per_second_t vx, units::feet_per_second_t vy, units::degrees_per_second_t omega) override;
        virtual void Drive(frc::ChassisSpeeds speed) override;
        virtual void Drive(std::vector<frc::SwerveModuleState> &state) override;
        virtual bool GetIdleMode() override;
        virtual void SetIdleMode(bool idle_mode) override;
        virtual void SetRobotOriented() override;
        virtual void SetFieldOriented() override;
        virtual bool GetOrientedMode() override; 
        virtual frc::Pose2d GetPose() override;
        virtual void ResetPose(frc::Pose2d pose) override;
        virtual frc::ChassisSpeeds GetRobotRelativeSpeeds() override;
        void UpdatePoseWithVision(frc::Pose3d pose3d, units::second_t timestamp);
        void SetShouldSwerveLock(bool shouldLock);

        inline std::array<SwerveModule*, 4>* GetModules()
        {
            return &m_modules;
        }
        // ###########################################################
        // #                  Front Left Module                      #
        // ###########################################################
        // --------------------Absolute Encoder-----------------------
        const int FL_ABS_ENC_PORT = 3;
        const bool FL_ABS_ENC_INVERTED = false;
        const frc::Rotation2d FL_ZERO_HEADING{units::degree_t{268.76f}};

        ctre::phoenix6::hardware::CANcoder fl_abs_enc{FL_ABS_ENC_PORT};

        // -----------------------Turn Motor--------------------------
        const int FL_TURN_MTR_ID = 15;
        const bool FL_TURN_MTR_INVERTED = true;

        rev::spark::SparkMax fl_turn_mtr{FL_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder fl_turn_enc = fl_turn_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController fl_turn_pid = fl_turn_mtr.GetClosedLoopController();

        // -----------------------Drive Motor-------------------------
        const int FL_DRIVE_MTR_ID = 18;
        const double FL_POSITION_CORRECTION_FACTOR = 1.0;

        rev::spark::SparkMax fl_drive_mtr{FL_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder fl_drive_enc = fl_drive_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController fl_drive_pid = fl_drive_mtr.GetClosedLoopController();


        // ###########################################################
        // #                  Front Right Module                     #
        // ###########################################################
        // --------------------Absolute Encoder-----------------------
        const int FR_ABS_ENC_PORT = 6;
        const bool FR_ABS_ENC_INVERTED = false;
        const frc::Rotation2d FR_ZERO_HEADING{units::degree_t{270.61f}};

        ctre::phoenix6::hardware::CANcoder fr_abs_enc{FR_ABS_ENC_PORT};

        // -----------------------Turn Motor--------------------------
        const int FR_TURN_MTR_ID = 17;
        const bool FR_TURN_MTR_INVERTED = true;

        rev::spark::SparkMax fr_turn_mtr{FR_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder fr_turn_enc = fr_turn_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController fr_turn_pid = fr_turn_mtr.GetClosedLoopController();

        // -----------------------Drive Motor-------------------------
        const int FR_DRIVE_MTR_ID = 19;
        const double FR_POSITION_CORRECTION_FACTOR = 1.0;

        rev::spark::SparkMax fr_drive_mtr{FR_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder fr_drive_enc = fr_drive_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController fr_drive_pid = fr_drive_mtr.GetClosedLoopController(); 


        // ###########################################################
        // #                  Back Left Module                       #
        // ###########################################################
        // --------------------Absolute Encoder-----------------------
        const int BL_ABS_ENC_PORT = 12;
        const bool BL_ABS_ENC_INVERTED = false;
        const frc::Rotation2d BL_ZERO_HEADING{units::degree_t{3.86f}};

        ctre::phoenix6::hardware::CANcoder bl_abs_enc{BL_ABS_ENC_PORT};


        // -----------------------Turn Motor--------------------------
        const int BL_TURN_MTR_ID = 7;
        const bool BL_TURN_MTR_INVERTED = true;

        rev::spark::SparkMax bl_turn_mtr{BL_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder bl_turn_enc = bl_turn_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController bl_turn_pid = bl_turn_mtr.GetClosedLoopController();

        // -----------------------Drive Motor-------------------------
        const int BL_DRIVE_MTR_ID = 8;
        const double BL_POSITION_CORRECTION_FACTOR = 1.0;

        rev::spark::SparkMax bl_drive_mtr{BL_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder bl_drive_enc = bl_drive_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController bl_drive_pid = bl_drive_mtr.GetClosedLoopController();


        // ###########################################################
        // #                  Back Right Module                      #
        // ###########################################################
        // --------------------Absolute Encoder-----------------------
        const int BR_ABS_ENC_PORT = 9;
        const bool BR_ABS_ENC_INVERTED = false;
        const frc::Rotation2d BR_ZERO_HEADING{units::degree_t{176.48f}};

        ctre::phoenix6::hardware::CANcoder br_abs_enc{BR_ABS_ENC_PORT};

        // -----------------------Turn Motor--------------------------
        const int BR_TURN_MTR_ID = 2;
        const bool BR_TURN_MTR_INVERTED = true;

        rev::spark::SparkMax br_turn_mtr{BR_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder br_turn_enc = br_turn_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController br_turn_pid = br_turn_mtr.GetClosedLoopController();

        // -----------------------Drive Motor-------------------------
        const int BR_DRIVE_MTR_ID = 20;
        const double BR_POSITION_CORRECTION_FACTOR = 1.0;

        rev::spark::SparkMax br_drive_mtr{BR_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkRelativeEncoder br_drive_enc = br_drive_mtr.GetEncoder();
        rev::spark::SparkClosedLoopController br_drive_pid = br_drive_mtr.GetClosedLoopController(); 


        // ###########################################################
        // #                     Swerve Drive                        #
        // ###########################################################
        const double ROBOT_WIDTH_M = 0.617;
        const double ROBOT_LENGTH_M = 0.617;

        const frc::Translation2d fl_position{units::meter_t{ROBOT_LENGTH_M / 2.0}, units::meter_t{ROBOT_WIDTH_M / 2.0}};
        const frc::Translation2d fr_position{units::meter_t{ROBOT_LENGTH_M / 2.0}, units::meter_t{-ROBOT_WIDTH_M / 2.0}};
        const frc::Translation2d bl_position{units::meter_t{-ROBOT_LENGTH_M / 2.0}, units::meter_t{ROBOT_WIDTH_M / 2.0}};
        const frc::Translation2d br_position{units::meter_t{-ROBOT_LENGTH_M / 2.0}, units::meter_t{-ROBOT_WIDTH_M / 2.0}};

        // ------------------------Turn Motor-------------------------
        const double TURN_GEAR_RATIO = 10.2857;
        const double MOTOR_ROT_TO_DEG = 360.0 / TURN_GEAR_RATIO;

        const double TURN_P = 0.045;
        const double TURN_I = 0.0;
        const double TURN_D = 0.003;
        const double TURN_FF = 0.0;

        // ------------------------Drive Motor------------------------
        const double DRIVE_GEAR_RATIO = 5.5;
        const double WHEEL_DIAMETER_FT = 0.333; // 4 inches
        const double MOTOR_ROT_TO_FT = (WHEEL_DIAMETER_FT * 3.14159) / DRIVE_GEAR_RATIO;

        const double DRIVE_P = 0.08;
        const double DRIVE_I = 0.0;
        const double DRIVE_D = 0.1;
        const double DRIVE_FF = 0.0;

        // --------------------------Gyro-----------------------------
        const bool GYRO_INVERTED = true;
        const frc::Rotation2d GYRO_ZERO_HEADING{units::degree_t{0.0f}};

        // --------------------------Swerve---------------------------
        const double MAX_DRIVE_SPEED_FPS = 18.0;
        const double MAX_ANGULAR_VELOCITY_DEGPS = 540.0;
        const double CONTROLLER_DEADZONE = 0.1;
        const int TURN_MOTOR_CURRENT_LIMIT = 20;
        const int DRIVE_MOTOR_CURRENT_LIMIT = 30;
        const double SWERVE_VOLTAGE_COMPENSATION = 10.5;
        const bool IS_DRIVE_IN_COAST = false;
        const bool IS_ROBOT_ORIENTED_DRIVE = false;
    private:
        frc::Field2d m_field;
        frc::Translation2d m_frontLeftLocation;
        frc::Translation2d m_frontRightLocation;
        frc::Translation2d m_backLeftLocation;
        frc::Translation2d m_backRightLocation;

        frc::SwerveDriveKinematics<4>* m_kinematics;
        
        std::array<SwerveModule*, 4> m_modules;

        std::vector<frc::SwerveModuleState> m_states;

        double m_maxDriveSpeed;
        double m_maxTurnSpeed;
        bool m_ebrake = false;
        bool m_driveMotorIdleMode = false;
        // false is brake and true is coast
        bool m_orientation = false;
        // false is robot orientated, true is FieldOrientated. 
        double m_deadzone;

        bool m_visionResetOccurred = false;

        double ApplyDeadzone(double input);
        std::pair<double, double> ApplyCylindricalDeadzone(double x, double y);
        SwerveGyro *m_gyro;
        frc::SwerveDrivePoseEstimator<4> *m_estimator;

        bool m_shouldSwerveLock = true;
};