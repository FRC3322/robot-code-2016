// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Intake> Robot::intake;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    drivetrain.reset(new Drivetrain());
    shooter.reset(new Shooter());
    intake.reset(new Intake());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());
	autonomousCommand.reset(new autonCommand());
	ahrs = RobotMap::ahrs;

	SmartDashboard::PutNumber("front speed",0),SmartDashboard::PutNumber("rear speed",0),
	SmartDashboard::PutNumber("front P",0),SmartDashboard::PutNumber("front I",0),SmartDashboard::PutNumber("front D",0),
	SmartDashboard::PutNumber("rear P",0),SmartDashboard::PutNumber("rear I",0),SmartDashboard::PutNumber("rear D",0);
	SmartDashboard::PutBoolean("testShooterPID",false);

	SmartDashboard::PutNumber("Auton Number: ",0);

	//Talon SRX 15 mode bug
	Robot::drivetrain->EnableSRX();
	Robot::shooter->initShooter();

}

/**
 *
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	Robot::drivetrain->EnableSRX();
	Robot::shooter->initShooter();

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
	Robot::drivetrain->EnableSRX();
	Robot::drivetrain->EnableSRX();
	Robot::shooter->initShooter();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	Robot::TestNavX();


}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
	Robot::drivetrain->EnableSRX();
	Robot::shooter->initShooter();
	rotateCommand.release();
}

void Robot::TestNavX(){
	SmartDashboard::PutNumber("Angle", RobotMap::ahrs->GetAngle());
	SmartDashboard::PutNumber("Altitude (meters)", RobotMap::ahrs->GetAltitude());
	SmartDashboard::PutNumber("Compass Heading (degrees, 0-360)", RobotMap::ahrs->GetCompassHeading());
	SmartDashboard::PutNumber("Pitch (x axis rotation, -180-180)", RobotMap::ahrs->GetPitch());
	SmartDashboard::PutNumber("Rate (rate of z axis rotation, degrees/second)", RobotMap::ahrs->GetRate());
	SmartDashboard::PutNumber("Temperature (degrees celcius)", RobotMap::ahrs->GetTempC());
	SmartDashboard::PutNumber("Vel X (meters/second, not accurate)", RobotMap::ahrs->GetVelocityX());
	SmartDashboard::PutNumber("Vel Y (meters/second, not accurate)", RobotMap::ahrs->GetVelocityY());
	SmartDashboard::PutNumber("Vel Z (meters/second, not accurate)", RobotMap::ahrs->GetVelocityZ());
	SmartDashboard::PutNumber("Yaw (z axis rotation,-180 to 180)",RobotMap::ahrs->GetYaw());

}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	//ahrs (NavX) testing.  Should be disabled / commented out during competitions to reduce overhead
	Robot::TestNavX();

	SmartDashboard::PutNumber("vel",Robot::shooter->returnVel());

	SmartDashboard::PutNumber("amp",Robot::shooter->returnAmpVal());
	SmartDashboard::PutNumber("volts",Robot::shooter->returnVoltVal());

	Robot::drivetrain->getDrive()->ArcadeDrive(Robot::oi->getdriveStick()->GetRawAxis(4),-1*Robot::oi->getdriveStick()->GetY(),true);
	if(Robot::oi->getdriveStick()->GetRawButton(7)){
		Robot::shooter->shootRaw();
	}
	else{
		Robot::shooter->stopShooter();
	}

	if(Robot::oi->getdriveStick()->GetRawButton(1)){
		Robot::intake->takeBallIn();
	}

	//test function for the PID velocity control on the shooter.  Should also be disabled/commented out during competitions, and only used for testing purposes.
	if(SmartDashboard::GetBoolean("testShooterPID",false)){
		Robot::shooter->testPID(SmartDashboard::GetNumber("front speed",0),SmartDashboard::GetNumber("rear speed",0),
								SmartDashboard::GetNumber("front P",0),SmartDashboard::GetNumber("front I",0),SmartDashboard::GetNumber("front D",0),
								SmartDashboard::GetNumber("rear P",0),SmartDashboard::GetNumber("rear I",0),SmartDashboard::GetNumber("rear D",0));
	}


}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

