// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef CAT_A_H
#define CAT_A_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class CatA: public Subsystem {
private:
	double lastError;
	double iTerm;
	double setpoint;
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	CatA();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	std::shared_ptr<CANTalon> catA1;
	std::shared_ptr<CANTalon> catA2;
	//double calculatePID(double setpoint, double current, double p, double i, double d);
	bool isMoving();
	void moveArm();
	void initPID();
	double computePID(double target, double encPos, double kP, double kI, double kD, double kF);
	void portcollisInit();
	void portcollisLift();
	void chivelDeFrise();
	void init();
//	void setPosition(int setpoint, float p, float i, float d, float f);
	void lower();
	void stop();
	/*double f;
	double iVal = 0;
	double previousIVal = 0;
	double pi = 3.1415;
	double previous = 0;
	double maxEncoder = 0;
	double previousError = 0; */
};

#endif
