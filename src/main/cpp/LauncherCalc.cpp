#include "LauncherCalc.h"
#include <frc/DriverStation.h>

LauncherCalc::LauncherCalc()
{
    //just placeholder map values for now, change later please
    //Distance (Bumper to Hub) - RPM

// 12 in - 2700

// 25in-3000

// 40in-3200

// 52in-3300

// 64in-3500

// 77 in - 4000

    // hoodAngleMap.insert(1,1);
    // hoodAngleMap.insert(2,2);
    // hoodAngleMap.insert(3,3);
    flywheelRPMMap.insert(0.3048, 2750); //what unit does it take for distance
    flywheelRPMMap.insert(0.635, 3050);
    flywheelRPMMap.insert(1.016, 3250);
    flywheelRPMMap.insert(1.3208, 3350);
    flywheelRPMMap.insert(1.6256, 3550);
    flywheelRPMMap.insert(1.9558, 4050);
    // timeOfFlightMap.insert(1, 1);
    // timeOfFlightMap.insert(2, 2);
    // timeOfFlightMap.insert(3, 3);
}

double LauncherCalc::Calculate(double distance, frc::Pose2d current, double velocityX, double velocityY)
{
    return flywheelRPMMap.operator[](distance);
}
