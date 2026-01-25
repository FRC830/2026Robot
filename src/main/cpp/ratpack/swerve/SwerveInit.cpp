#include "Robot.h"
#include "ratpack/swerve/SwerveConfig.h"

  namespace ModulePosition
  { 
    static const int FL = 0;
    static const int FR = 1;
    static const int BL  = 2;
    static const int BR  = 3; 
  };


void Robot::SwerveInit(){
  AbsoluteEncoderConfig abs_config;

  abs_config.encoder = &_swerve.fl_abs_enc;
  abs_config.is_inverted = _swerve.FL_ABS_ENC_INVERTED;
  abs_config.zero_heading = _swerve.FL_ZERO_HEADING;
  _abs_encoders[ModulePosition::FL].Configure(abs_config);

  abs_config.encoder = &_swerve.fr_abs_enc;
  abs_config.is_inverted = _swerve.FR_ABS_ENC_INVERTED;
  abs_config.zero_heading = _swerve.FR_ZERO_HEADING;
  _abs_encoders[ModulePosition::FR].Configure(abs_config);

  abs_config.encoder = &_swerve.bl_abs_enc;
  abs_config.is_inverted = _swerve.BL_ABS_ENC_INVERTED;
  abs_config.zero_heading = _swerve.BL_ZERO_HEADING;
  _abs_encoders[ModulePosition::BL].Configure(abs_config);

  abs_config.encoder = &_swerve.br_abs_enc;
  abs_config.is_inverted = _swerve.BR_ABS_ENC_INVERTED;
  abs_config.zero_heading = _swerve.BR_ZERO_HEADING;
  _abs_encoders[ModulePosition::BR].Configure(abs_config);


  SwerveTurnMotorConfig turn_config;
  turn_config.p=_swerve.TURN_P;  
  turn_config.i=_swerve.TURN_I;
  turn_config.d=_swerve.TURN_D;
  turn_config.ff=_swerve.TURN_FF;
  turn_config.ratio=_swerve.MOTOR_ROT_TO_DEG;
  turn_config.swerve_voltage_compensation = _swerve.SWERVE_VOLTAGE_COMPENSATION;
  turn_config.turn_motor_current_limit = _swerve.TURN_MOTOR_CURRENT_LIMIT;

  turn_config.deviceID=_swerve.FL_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::FL];
  turn_config.inverted=_swerve.FL_TURN_MTR_INVERTED;
  turn_config.PID=&_swerve.fl_turn_pid;
  turn_config.relative_Encoder=&_swerve.fl_turn_enc;
  turn_config.turn_motor=&_swerve.fl_turn_mtr;
  _turn_motors[ModulePosition::FL].Configure(turn_config);

  turn_config.deviceID=_swerve.FR_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::FR];
  turn_config.inverted=_swerve.FR_TURN_MTR_INVERTED;
  turn_config.PID=&_swerve.fr_turn_pid;
  turn_config.relative_Encoder=&_swerve.fr_turn_enc;
  turn_config.turn_motor=&_swerve.fr_turn_mtr;
  _turn_motors[ModulePosition::FR].Configure(turn_config);

  turn_config.deviceID=_swerve.BL_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::BL];
  turn_config.inverted=_swerve.BL_TURN_MTR_INVERTED;
  turn_config.PID=&_swerve.bl_turn_pid;
  turn_config.relative_Encoder=&_swerve.bl_turn_enc;
  turn_config.turn_motor=&_swerve.bl_turn_mtr;
  _turn_motors[ModulePosition::BL].Configure(turn_config);

  turn_config.deviceID=_swerve.BR_TURN_MTR_ID;
  turn_config.absouluteEncoder=&_abs_encoders[ModulePosition::BR];
  turn_config.inverted=_swerve.BR_TURN_MTR_INVERTED;
  turn_config.PID=&_swerve.br_turn_pid;
  turn_config.relative_Encoder=&_swerve.br_turn_enc;
  turn_config.turn_motor=&_swerve.br_turn_mtr;
  _turn_motors[ModulePosition::BR].Configure(turn_config);


  SwerveDriveMotorConfig drive_config;
  drive_config.p = _swerve.DRIVE_P;
  drive_config.i = _swerve.DRIVE_I;
  drive_config.d = _swerve.DRIVE_D;
  drive_config.ff = _swerve.DRIVE_FF;
  drive_config.ratio = _swerve.MOTOR_ROT_TO_FT / 60.0;
  drive_config.drive_motor_current_limit = _swerve.DRIVE_MOTOR_CURRENT_LIMIT;
  drive_config.swerve_voltage_compensation = _swerve.SWERVE_VOLTAGE_COMPENSATION;
  drive_config.idleMode = _swerve.IS_DRIVE_IN_COAST ? rev::spark::SparkMaxConfig::IdleMode::kCoast : rev::spark::SparkMaxConfig::IdleMode::kBrake;
  
  drive_config.PID = &_swerve.fl_drive_pid;
  drive_config.encoder = &_swerve.fl_drive_enc;
  drive_config.motor = &_swerve.fl_drive_mtr;
  drive_config.correction_factor = _swerve.FL_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::FL].Configure(drive_config);

  drive_config.PID = &_swerve.fr_drive_pid;
  drive_config.encoder = &_swerve.fr_drive_enc;
  drive_config.motor = &_swerve.fr_drive_mtr;
  drive_config.correction_factor = _swerve.FR_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::FR].Configure(drive_config);

  drive_config.PID = &_swerve.bl_drive_pid;
  drive_config.encoder = &_swerve.bl_drive_enc;
  drive_config.motor = &_swerve.bl_drive_mtr;
  drive_config.correction_factor = _swerve.BL_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::BL].Configure(drive_config);

  drive_config.PID = &_swerve.br_drive_pid;
  drive_config.encoder = &_swerve.br_drive_enc;
  drive_config.motor = &_swerve.br_drive_mtr;
  drive_config.correction_factor = _swerve.BR_POSITION_CORRECTION_FACTOR;
  _drive_motors[ModulePosition::BR].Configure(drive_config);


  SwerveModuleConfig module_config;
  module_config.idleMode=true;

  for (int i = 0; i < NUM_MODULES; ++i)
  {
    module_config.driveMotor = &_drive_motors[i];
    module_config.turnMotor  = &_turn_motors[i];
    _modules[i].Configure(module_config);
  }
  
  GyroConfig gyroConfig;
  gyroConfig.is_inverted = _swerve.GYRO_INVERTED;
  gyroConfig.zero_heading = _swerve.GYRO_ZERO_HEADING;
  _gyro.Configure(gyroConfig);

  SwerveConfig swerveConfig;
  swerveConfig.backLeftLocation= _swerve.bl_position;
  swerveConfig.backRightLocation=_swerve.br_position;
  swerveConfig.ebrake=false;
  swerveConfig.frontLeftLocation=_swerve.fl_position;
  swerveConfig.frontRightLocation=_swerve.fr_position;
  swerveConfig.idle_mode=_swerve.IS_DRIVE_IN_COAST;
  swerveConfig.maxDriveSpeed=_swerve.MAX_DRIVE_SPEED_FPS;
  swerveConfig.maxTurnSpeed=_swerve.MAX_ANGULAR_VELOCITY_DEGPS;
  swerveConfig.orientation=_swerve.IS_ROBOT_ORIENTED_DRIVE;
  swerveConfig.deadzone=_swerve.CONTROLLER_DEADZONE;
  swerveConfig.gyro=&_gyro;
  auto* temp = _swerve.GetModules();
  for (int i = 0; i < 4; ++i)
  {
    (*temp)[i] = &_modules[i];
  }
  _swerve.Configure(swerveConfig);
  _swerve.SetFieldOriented();
}

void Robot::PrintSwerveInfo()
{
  frc::SmartDashboard::PutNumber("FL Drive Motor Rotations", _swerve.fl_drive_enc.GetPosition());
  frc::SmartDashboard::PutNumber("FR Drive Motor Rotations", _swerve.fr_drive_enc.GetPosition());
  frc::SmartDashboard::PutNumber("BR Drive Motor Rotations", _swerve.br_drive_enc.GetPosition());
  frc::SmartDashboard::PutNumber("BL Drive Motor Rotations", _swerve.bl_drive_enc.GetPosition());

// Raw heading of absolute encoders
  frc::SmartDashboard::PutNumber("FL Raw Heading", double(_abs_encoders[0].GetRawHeading().Degrees()));
  frc::SmartDashboard::PutNumber("FR Raw Heading", double(_abs_encoders[1].GetRawHeading().Degrees()));
  frc::SmartDashboard::PutNumber("BL Raw Heading", double(_abs_encoders[2].GetRawHeading().Degrees()));
  frc::SmartDashboard::PutNumber("BR Raw Heading", double(_abs_encoders[3].GetRawHeading().Degrees()));
  frc::SmartDashboard::PutNumber("Gyro Raw Heading", _gyro.GetRawHeading().Degrees().to<double>());

  // Heading of turn motors
  frc::SmartDashboard::PutNumber("FL Heading", double(_abs_encoders[0].GetHeading().Degrees()));
  frc::SmartDashboard::PutNumber("FR Heading", double(_abs_encoders[1].GetHeading().Degrees()));
  frc::SmartDashboard::PutNumber("BL Heading", double(_abs_encoders[2].GetHeading().Degrees()));
  frc::SmartDashboard::PutNumber("BR Heading", double(_abs_encoders[3].GetHeading().Degrees()));
  frc::SmartDashboard::PutNumber("Gyro Heading", _gyro.GetHeading().Degrees().to<double>());

  // Velocity of drive motors
  frc::SmartDashboard::PutNumber("FL Velocity", _swerve.fl_drive_enc.GetVelocity());
  frc::SmartDashboard::PutNumber("FR Velocity", _swerve.fr_drive_enc.GetVelocity());
  frc::SmartDashboard::PutNumber("BL Velocity", _swerve.bl_drive_enc.GetVelocity());
  frc::SmartDashboard::PutNumber("BR Velocity", _swerve.br_drive_enc.GetVelocity());

}

double Robot::GetSwerveDeadZone()
{
  return _swerve.CONTROLLER_DEADZONE;
}