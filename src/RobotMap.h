// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"
#include "AHRS.h"



/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<CANTalon> drivetraindriveSRX1;
	static std::shared_ptr<CANTalon> drivetraindriveSRX2;
	static std::shared_ptr<CANTalon> drivetraindriveSRX3;
	static std::shared_ptr<CANTalon> drivetraindriveSRX4;
	static std::shared_ptr<RobotDrive> drivetraindriveTrain;
	static std::shared_ptr<PowerDistributionPanel> drivetrainpowerDistPanel;
	static std::shared_ptr<DoubleSolenoid> drivetraingearshiftRight;
	static std::shared_ptr<DoubleSolenoid> drivetraingearshiftLeft;
	static std::shared_ptr<CANTalon> shootershooterTalon1;
	static std::shared_ptr<CANTalon> shootershooterTalon2;
	static std::shared_ptr<CANTalon> intakeintakeSpinTalon1;
	static std::shared_ptr<CANTalon> intakeintakeSpinTalon2;
	static std::shared_ptr<CANTalon> intakeintakeRotateTalon1;
	static std::shared_ptr<CANTalon> intakeintakeRotateTalon2;
	static std::shared_ptr<CANTalon> catACatA1;
	static std::shared_ptr<CANTalon> catACatA2;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	//navx
	static std::shared_ptr<AHRS> ahrs;

	static std::shared_ptr<PIDController> turnController;
	static std::shared_ptr<PIDController> intakePID;
	static std::shared_ptr<Encoder> intakeEncoder;
	static std::shared_ptr<PIDController> catAPID;
	static std::shared_ptr<Encoder> catAEncoder;
	static std::shared_ptr<Potentiometer> pot;
	static std::shared_ptr<Potentiometer> intakePot;


	static void init();
};
#endif
