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
    flywheelRPMMap.insert(12, 2700); //what unit does it take for distance
    flywheelRPMMap.insert(25, 3000);
    flywheelRPMMap.insert(40, 3200);
    flywheelRPMMap.insert(52, 3300);
    flywheelRPMMap.insert(64, 3500);
    flywheelRPMMap.insert(77, 4000);
    // timeOfFlightMap.insert(1, 1);
    // timeOfFlightMap.insert(2, 2);
    // timeOfFlightMap.insert(3, 3);
}

LauncherParam LauncherCalc::Calculate(double distance, frc::Pose2d current, double velocityX, double velocityY)
{
    LauncherParam calc;
    
    double timeOfFlight;
    double hoodAngle;
    double flywheelRPM;
    double aimAngle;
    frc::Pose2d lookaheadPose;
    double lookaheadLauncherToTargetDistance = distance;
    frc::Translation2d targetPosition;

    for(int i = 0; i<6; i++){
        timeOfFlight = timeOfFlightMap.operator[](distance);
        double offsetX = velocityX * calc.timeOfFlight;
        double offsetY = velocityY * calc.timeOfFlight;
        //lookaheadPose = frc::Pose2d(current.Translation().operator+(frc::Translation2d(units::meter_t(offsetX),units::meter_t(offsetY))), current.Rotation());

        bool blueAlliance = frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kBlue;

        //double x = lookaheadPose.X().value();
        //double y = lookaheadPose.Y().value();
        
        double x = current.X().value();
        double y = current.Y().value();

        if (blueAlliance)
        {
            double targetangle = atan2(4.035 - y,4.626 - x);
            targetPosition = frc::Translation2d( units::length::meter_t(4.626 - x),units::length::meter_t(4.035 - y));
        }
        else
        {
            double targetangle = atan2(4.035 - y, 11.915 - x);
            targetPosition= frc::Translation2d(units::length::meter_t(11.915 - x),units::length::meter_t(4.035 - y));
        }
            
        lookaheadLauncherToTargetDistance = targetPosition.Norm().value();
    }
    //aimAngle = atan2(targetPosition.Y().value()-lookaheadPose.Y().value(), targetPosition.X().value()-lookaheadPose.X().value());
    aimAngle = atan2(targetPosition.Y().value()-current.Y().value(), targetPosition.X().value()-current.X().value());
    flywheelRPM = flywheelRPMMap.operator[](distance);
    hoodAngle = hoodAngleMap.operator[](distance);

    calc.flywheelRPM = flywheelRPM;
    calc.hoodAngle = hoodAngle;
    calc.aimAngleRad = aimAngle;
    calc.timeOfFlight = timeOfFlight;
    return calc;
}