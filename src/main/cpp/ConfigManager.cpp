// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "ConfigManager.h"
#include <fmt/core.h>

namespace ratbot {

void ConfigManager::Initialize() {
    fmt::print("ConfigManager: Initializing preferences...\n");
    
    InitializeLauncher();
    InitializeIntake();
    InitializeMovement();
    InitializeSpindexer();
    InitializeGeneral();
    
    // Load initial values from Preferences
    Reload();
    
    fmt::print("ConfigManager: Initialization complete\n");
}

void ConfigManager::Reload() {
    ReloadLauncher();
    ReloadIntake();
    ReloadMovement();
    ReloadSpindexer();
    ReloadGeneral();
}

// ==================== Launcher Configuration ====================

void ConfigManager::InitializeLauncher() {
    // Flywheel PID values
    frc::Preferences::InitDouble("Launcher/Flywheel/P", 0.0);
    frc::Preferences::InitDouble("Launcher/Flywheel/I", 0.0);
    frc::Preferences::InitDouble("Launcher/Flywheel/D", 0.0);
    frc::Preferences::InitDouble("Launcher/Flywheel/kV", 0.0105);
    frc::Preferences::InitDouble("Launcher/Flywheel/kA", 0.008);
    frc::Preferences::InitDouble("Launcher/Flywheel/VelConvFactor", 1.0);
    frc::Preferences::InitDouble("Launcher/Flywheel/CurrentLimit", 30.0);
    
    // Indexer configuration
    frc::Preferences::InitDouble("Launcher/Indexer/CurrentLimit", 20.0);
}

void ConfigManager::ReloadLauncher() {
    launcher.flywheel_p = frc::Preferences::GetDouble("Launcher/Flywheel/P");
    launcher.flywheel_i = frc::Preferences::GetDouble("Launcher/Flywheel/I");
    launcher.flywheel_d = frc::Preferences::GetDouble("Launcher/Flywheel/D");
    launcher.flywheel_kv = frc::Preferences::GetDouble("Launcher/Flywheel/kV");
    launcher.flywheel_ka = frc::Preferences::GetDouble("Launcher/Flywheel/kA");
    launcher.flywheel_vel_conv_factor = frc::Preferences::GetDouble("Launcher/Flywheel/VelConvFactor");
    launcher.flywheel_current_limit = frc::Preferences::GetDouble("Launcher/Flywheel/CurrentLimit");
    launcher.indexer_current_limit = frc::Preferences::GetDouble("Launcher/Indexer/CurrentLimit");
}

// ==================== Intake Configuration ====================

void ConfigManager::InitializeIntake() {
    frc::Preferences::InitDouble("Intake/RollerSpeed", 0.95);
    frc::Preferences::InitDouble("Intake/AngleSpeed", 0.1);
    frc::Preferences::InitDouble("Intake/DownLocation", 0.25);
}

void ConfigManager::ReloadIntake() {
    intake.roller_speed = frc::Preferences::GetDouble("Intake/RollerSpeed");
    intake.angle_speed = frc::Preferences::GetDouble("Intake/AngleSpeed");
    intake.down_location = frc::Preferences::GetDouble("Intake/DownLocation");
}

// ==================== Movement Configuration ====================

void ConfigManager::InitializeMovement() {
    frc::Preferences::InitDouble("Movement/MaxTurnSpeed", 720.0);
    frc::Preferences::InitDouble("Movement/TurnFeedForward", 20.0);
    frc::Preferences::InitDouble("Movement/MaxSpeed", 1.32);
    frc::Preferences::InitDouble("Movement/SpeedFeedForward", 0.1);
}

void ConfigManager::ReloadMovement() {
    movement.max_turn_speed_deg_per_sec = frc::Preferences::GetDouble("Movement/MaxTurnSpeed");
    movement.turn_feed_forward = frc::Preferences::GetDouble("Movement/TurnFeedForward");
    movement.max_speed_m_per_sec = frc::Preferences::GetDouble("Movement/MaxSpeed");
    movement.speed_feed_forward = frc::Preferences::GetDouble("Movement/SpeedFeedForward");
}

// ==================== Spindexer Configuration ====================

void ConfigManager::InitializeSpindexer() {
    frc::Preferences::InitDouble("Spindexer/DefaultSpeed", 0.8);
}

void ConfigManager::ReloadSpindexer() {
    spindexer.default_speed = frc::Preferences::GetDouble("Spindexer/DefaultSpeed");
}

// ==================== General Configuration ====================

void ConfigManager::InitializeGeneral() {
    frc::Preferences::InitDouble("General/VoltageCompensation", 10.5);
}

void ConfigManager::ReloadGeneral() {
    general.voltage_compensation = frc::Preferences::GetDouble("General/VoltageCompensation");
}

} // namespace ratbot
