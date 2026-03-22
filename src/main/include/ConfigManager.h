// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Preferences.h>
#include <memory>
#include "ScoringPositionMap.h"

namespace ratbot {

/**
 * @brief Centralized configuration manager using WPILib Preferences API and JSON files.
 * 
 * This singleton class manages all robot configuration values, providing:
 * - Tunable parameters via NetworkTables/Shuffleboard (Preferences API)
 * - Complex data structures loaded from JSON files
 * - Single point of access for all configuration
 * - Optional live reloading for on-the-fly tuning
 * 
 * Usage:
 *   auto& config = ConfigManager::GetInstance();
 *   config.Initialize();  // Call once in RobotInit
 *   double kV = config.launcher.flywheel_kv;  // Access values
 *   config.Reload();  // Optional: reload from Preferences (e.g., in Periodic)
 */
class ConfigManager {
public:
    // Singleton pattern - get the single instance
    static ConfigManager& GetInstance() {
        static ConfigManager instance;
        return instance;
    }
    
    // Delete copy/move constructors and assignment operators
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    ConfigManager(ConfigManager&&) = delete;
    ConfigManager& operator=(ConfigManager&&) = delete;
    
    /**
     * @brief Initialize all preferences with default values.
     * Call this once in RobotInit().
     */
    void Initialize();
    
    /**
     * @brief Reload values from Preferences API.
     * Call this in RobotPeriodic() or TeleopPeriodic() for live tuning,
     * or just once after Initialize() if you don't need live updates.
     */
    void Reload();
    
    // Launcher configuration
    struct LauncherConfig {
        // Flywheel PID constants
        double flywheel_p;
        double flywheel_i;
        double flywheel_d;
        double flywheel_kv;
        double flywheel_ka;
        double flywheel_vel_conv_factor;
        double flywheel_current_limit;
        
        // Indexer configuration
        double indexer_current_limit;
    } launcher;
    
    // Intake configuration
    struct IntakeConfig {
        double roller_speed;
        double angle_speed;
        double down_location;
    } intake;
    
    // Movement/DriveToPosition configuration
    struct MovementConfig {
        double max_turn_speed_deg_per_sec;
        double turn_feed_forward;
        double max_speed_m_per_sec;
        double speed_feed_forward;
    } movement;
    
    // Spindexer configuration
    struct SpindexerConfig {
        double default_speed;
    } spindexer;
    
    // General robot configuration
    struct GeneralConfig {
        double voltage_compensation;
    } general;
    
    // Scoring positions (loaded from JSON)
    ScoringPositionMap scoring_positions;
    
private:
    ConfigManager() = default;
    
    // Initialize each subsystem's preferences with defaults
    void InitializeLauncher();
    void InitializeIntake();
    void InitializeMovement();
    void InitializeSpindexer();
    void InitializeGeneral();
    
    // Reload each subsystem's values from Preferences
    void ReloadLauncher();
    void ReloadIntake();
    void ReloadMovement();
    void ReloadSpindexer();
    void ReloadGeneral();
};

} // namespace ratbot
