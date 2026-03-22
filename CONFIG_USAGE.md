# Runtime Configuration System

## What This Is

Instead of hardcoding every PID value and speed into the source code, we're using a configuration system that lets you change values at runtime. This means you can tune PID constants, adjust speeds, and modify field positions without rebuilding and redeploying code.

The system has two parts:
- **WPILib Preferences** for tunable numbers (PID gains, speeds, timeouts)
- **JSON files** for complex data like field positions

Everything is accessed through a single `ConfigManager` class so you don't have magic strings scattered everywhere.

## Basic Usage

In your subsystem code:

```cpp
#include "ConfigManager.h"

void MySubsystem::Initialize() {
    auto& config = ratbot::ConfigManager::GetInstance();
    
    // Just access the values you need
    m_pidController.SetP(config.launcher.flywheel_p);
    m_pidController.SetFF(config.launcher.flywheel_kv);
    m_intake.SetSpeed(config.intake.roller_speed);
    
    // Field positions work too
    auto pos = config.scoring_positions.getPosition(tag_id, ScoringLocation::L1_RIGHT);
}
```

## Tuning Values During Testing

Connect to the robot, open Shuffleboard or Glass, and navigate to NetworkTables → Preferences. You'll see all the config values organized by category (Launcher/Flywheel/kV, Intake/RollerSpeed, etc.).

Change any value you want - they save automatically and persist across reboots. If you enable live reload (see below), changes apply immediately. Otherwise they'll take effect next time you restart robot code.

## Live Reload (Optional)

By default, config values are loaded once at startup. If you want changes to apply instantly while the robot is running, uncomment this line in `Robot.cpp`:

```cpp
void Robot::RobotPeriodic() {
    // Uncomment for live tuning
    ratbot::ConfigManager::GetInstance().Reload();
}
```

This adds a tiny bit of overhead each loop, so probably don't do it during competition. Great for practice though.

## What's Configurable

| Thing | What's in it |
|-------|-------------|
| `launcher` | Flywheel PID constants, current limits |
| `intake` | Roller speeds, angle speeds, positions |
| `movement` | Max speeds, turn rates, feedforward |
| `spindexer` | Motor speeds |
| `general` | Voltage compensation, etc |
| `scoring_positions` | Field coordinates (loaded from JSON) |

All the Preferences keys follow the pattern `Category/Subcategory/Parameter`, like `Launcher/Flywheel/kV` or `Intake/RollerSpeed`.

## Files

Code:
- `src/main/include/ConfigManager.h`
- `src/main/cpp/ConfigManager.cpp`
- `src/main/include/ScoringPositionMap.h`

Data:
- Preferences get stored on the RoboRIO at `/home/lvuser/networktables.json`
- Scoring positions come from `src/main/deploy/scoring_positions.json`

## Editing Field Positions

Open `src/main/deploy/scoring_positions.json` and edit the coordinates:

```json
{
  "positions": {
    "6": {
      "L1_RIGHT": [13.953, 3.201, 120.0],
      "L1_LEFT": [13.667, 3.036, 120.0]
    }
  }
}
```

Format is `[x_meters, y_meters, angle_degrees]`. You need to redeploy code after changing this (but no recompile needed).

## Moving From Hardcoded Values

Before, you'd have:
```cpp
#include "MechanismConfig.h"
const double P = ratbot::LauncherConfig::Flywheel::P;
```

Now do:
```cpp
#include "ConfigManager.h"
auto& config = ratbot::ConfigManager::GetInstance();
double p = config.launcher.flywheel_p;
```

## Adding New Config Values

Want to add a new tunable value? Three steps:

1. Add it to the struct in `ConfigManager.h`:
```cpp
struct LauncherConfig {
    double my_new_value;
} launcher;
```

2. Set the default in `ConfigManager.cpp`:
```cpp
void ConfigManager::InitializeLauncher() {
    frc::Preferences::InitDouble("Launcher/MyNewValue", 0.5);
}
```

3. Load it in `ConfigManager.cpp`:
```cpp
void ConfigManager::ReloadLauncher() {
    launcher.my_new_value = frc::Preferences::GetDouble("Launcher/MyNewValue");
}
```

Then just use `config.launcher.my_new_value` anywhere you need it.

## Things to Keep Hardcoded

Don't put these in Preferences:
- CAN IDs
- DIO channel numbers
- Servo IDs
- Other hardware port numbers

These stay in `CanConfig.h` because they match physical wiring. Changing them at runtime without rewiring the robot makes no sense and will break things.

## Troubleshooting

**Values aren't updating?**
- Make sure you enabled live reload if you want instant changes
- Check the preference key name matches exactly (case sensitive)
- Try restarting robot code

**Scoring positions not loading?**
- Look at console output for errors
- Make sure `scoring_positions.json` is in `src/main/deploy/`
- If the JSON is bad, it falls back to hardcoded positions

**Don't see preferences in Shuffleboard?**
- Check NetworkTables → Preferences folder
- Make sure `ConfigManager::Initialize()` got called in Robot.cpp
- Look at robot console for initialization messages

## References

[WPILib Preferences docs](https://docs.wpilib.org/en/stable/docs/software/networktables/networktables-preferences.html)  
[Shuffleboard guide](https://docs.wpilib.org/en/stable/docs/software/dashboards/shuffleboard/index.html)
