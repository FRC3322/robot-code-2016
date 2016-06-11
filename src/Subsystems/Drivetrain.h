// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <pathfinder.h>

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public Subsystem, public PIDOutput {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<RobotDrive> driveTrain;
	std::shared_ptr<DoubleSolenoid> gearshiftRight;
	std::shared_ptr<DoubleSolenoid> gearshiftLeft;

public:
	Drivetrain();
	void InitDefaultCommand();
	std::shared_ptr<RobotDrive> getDrive();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	std::shared_ptr<CANTalon> driveSRX1;
	std::shared_ptr<CANTalon> driveSRX2;
	std::shared_ptr<CANTalon> driveSRX3;
	std::shared_ptr<CANTalon> driveSRX4;
	std::shared_ptr<PowerDistributionPanel> powerDistPanel;

	void EnableSRX();

	PIDController *turnController;

	int getVelocity(int currentGear);
	float driveToAngle(float velocity,float targetAngle);

	void waypointGenerator();

	void newdriveSystem(float f, float t, double yawRate);

    double rotateToAngleRate;
    float setpoint;

    virtual void PIDWrite(float output);
	void gearShift(int position);
	void autoShift();

	void Skvarek();

	void Schneyer();

	constexpr static double kP = 0.28f;
	constexpr static double kI = 0.00f;
	constexpr static double kD = 0.00f;
	constexpr static double kF = 0.00f;

	int currentSpeed;
	const int shiftHigh = 3693;
	const int shiftLow = 1617; //shift values need testing, buffer in between to avoid toggling in the middle
	int currentGear = 0; //0 = low, 1 = high

	double angleToTurn(double currentAngle, double targetAngle);

	double provisionalAngle;
	double targetAngle;
	double currentAngle;
	double calculatePID(double setpoint, double current, double p, double i, double d);
	double iVal = 0;
	double previousIVal = 0;
	double f;
	double pi = 3.1415;
	double previous = 0;
	double maxEncoder = 0;
	double previousError = 0;
    double errorRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double previousYawRate;
    int i = 0;
    double changeMagnitude(float val,float amount);

};

#endif
