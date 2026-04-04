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
    flywheelRPMMap.insert(2.8448, 3300); //what unit does it take for distance
    flywheelRPMMap.insert(2.032, 3100);
    flywheelRPMMap.insert(1.5748, 2900);
    flywheelRPMMap.insert(1.00584, 2800);
    flywheelRPMMap.insert(0.518, 2700);
    // flywheelRPMMap.insert(4.511, 4300);
    flywheelRPMMap.insert(1.372, 2750);
    flywheelRPMMap.insert(3.41, 3500);
    //14.9ft
    flywheelRPMMap.insert(4.54,4200);

    hoodMap.insert(2.8448,180);
    hoodMap.insert(2.032,155);
    hoodMap.insert(1.5748,130);
    hoodMap.insert(1.00584,50);
    hoodMap.insert(0.518,30);
    hoodMap.insert(4.54,180);
    hoodMap.insert(1.372, 135);
    hoodMap.insert(3.41,180);


    // timeOfFlightMap.insert(1, 1);    
    // timeOfFlightMap.insert(2, 2);
    // timeOfFlightMap.insert(3, 3);
}

double LauncherCalc::Calculate(double distance, frc::Pose2d current, double velocityX, double velocityY)
{
    return flywheelRPMMap.operator[](distance);
}

double LauncherCalc::CalcHood(double distance)
{
    return hoodMap.operator[](distance);
}