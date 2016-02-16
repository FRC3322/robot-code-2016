// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/autonCommand.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Shooter.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/teleopDrive.h"
#include "OI.h"
#include "xbox.h"
#include <thread>
#include <iostream>
#include <DoubleSolenoid.h>

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<Drivetrain> drivetrain;
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Intake> intake;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	virtual void TestNavX();
	void autoShift();
	void gearShift(int position);

	//command declarations
	std::unique_ptr<Command> driveTeleop;

	std::shared_ptr<AHRS> ahrs;

	int maxSpeed;
	int shiftHigh = 3693;
	int shiftLow = 1617; //shift values need testing, buffer in between to avoid toggling in the middle
	//shift into low gear, function not made
	int currentGear; //0 = low, 1 = high
};
#endif
