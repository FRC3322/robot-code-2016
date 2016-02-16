// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "rotateDrivetrain.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

rotateDrivetrain::rotateDrivetrain(): Command(), PIDOutput() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	const static double kP = 0.03f;
	const static double kI = 0.00f;
	const static double kD = 0.00f;
	const static double kF = 0.00f;

	const static double kToleranceDegrees = 2.0f;
	ahrs = RobotMap::ahrs;
	this->setpoint = setpoint;
	turnController = new PIDController(kP,kI,kD,kF,ahrs.get(),this);
	turnController->SetInputRange(-180.0f,180.0f);
	turnController->SetOutputRange(-1.0,1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR


// Called just before this Command runs the first time
void rotateDrivetrain::Initialize() {
	rotateToAngleRate = 0;
	turnController->Enable();
	turnController->SetSetpoint(setpoint);

}

// Called repeatedly when this Command is scheduled to run
void rotateDrivetrain::Execute() {
	Robot::drivetrain->getDrive()->ArcadeDrive(0,rotateToAngleRate,false);
}

// Make this return true when this Command no longer needs to run execute()
bool rotateDrivetrain::IsFinished() {
    return turnController->OnTarget();
}

// Called once after isFinished returns true
void rotateDrivetrain::End() {
	turnController->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void rotateDrivetrain::Interrupted() {

}

void rotateDrivetrain::PIDWrite(float output){
	rotateDrivetrain::rotateToAngleRate = output;
}
