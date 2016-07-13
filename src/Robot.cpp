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
#include <math.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<CatA> Robot::catA;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<TestRobot> testRobot;
bool prevRBumperState;
bool isShooting = false;
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    drivetrain.reset(new Drivetrain());
    shooter.reset(new Shooter());
    intake.reset(new Intake());
    catA.reset(new CatA());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    testRobot.reset(new TestRobot());
    // This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());
	autonomousCommand.reset(new autonCommand());
	ahrs = RobotMap::ahrs;
	Robot::drivetrain->gearShift(0);
	Robot::drivetrain->currentGear=0;

	SmartDashboard::PutNumber("Auton Number: ",0);

	//Talon SRX 15 mode bug
	Robot::drivetrain->EnableSRX();
	Robot::shooter->initShooter();
	Robot::intake->init();
	RobotMap::ahrs->ZeroYaw();
//	CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	SmartDashboard::PutNumber("P",.1);
	SmartDashboard::PutNumber("I", 0);
	SmartDashboard::PutNumber("D", .1);
	SmartDashboard::PutNumber("Decay", 0);
}
/*
 * Make sure our talons are not in a bad state - i.e. low voltage fault
 */
void clearStickyFaults() {
	RobotMap::drivetraindriveSRX1->ClearStickyFaults();
	RobotMap::drivetraindriveSRX2->ClearStickyFaults();
	RobotMap::drivetraindriveSRX3->ClearStickyFaults();
	RobotMap::drivetraindriveSRX4->ClearStickyFaults();

	RobotMap::shootershooterTalon1->ClearStickyFaults();
	RobotMap::shootershooterTalon2->ClearStickyFaults();

	RobotMap::intakeintakeSpinTalon1->ClearStickyFaults();
	RobotMap::intakeintakeSpinTalon2->ClearStickyFaults();
	RobotMap::intakeintakeRotateTalon1->ClearStickyFaults();
	RobotMap::intakeintakeRotateTalon2->ClearStickyFaults();

	RobotMap::catACatA1->ClearStickyFaults();
	RobotMap::catACatA2->ClearStickyFaults();
}

/**
 *
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */

void Robot::DisabledInit(){
	clearStickyFaults();
	Robot::catA->init();
	if(SmartDashboard::GetBoolean("Test Talons",false)){
		Robot::testRobot->runTest();
	}
	else{
		Robot::testRobot->resetSmartDashboard();
	}
}
/*
 * Called every 20ms during disabled mode
 */
void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("pot",RobotMap::pot->Get());//todo: which pot is this?  should be refactored
	SmartDashboard::PutNumber("intake pot",RobotMap::intakePot->Get());
	Robot::LogNavXValues();
}
/*
 * Called once as soon as we enter auton mode
 */
void Robot::AutonomousInit() {
	Robot::drivetrain->EnableSRX();
	Robot::toggleIntakeOff();
	Robot::drivetrain->gearShift(1);
	Robot::ahrs->ZeroYaw();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();

}
/*
 * called every 20ms during auton mode
 */
void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	int autonNumber = SmartDashboard::GetNumber("Auton Number: ",1);
	switch(autonNumber){
	case 1:
		//portcullis
		Robot::catA->portcollisInit();
		break;
	case 2:
		//chivel de frise
//		Robot::catA->chivelDeFrise();
		break;
	case 3:
		//rough terrain
		break;
	case 4:
		//moat
		break;
	case 5:
		//low bar simple
		Robot::catA->portcollisInit();
		break;
	case 6:
		//low bar with shot
		break;
	case 7:
		//do nothing
		break;
	case 8:
		//reach
		break;
	default:
		//portcullis
		Robot::catA->portcollisInit();
		break;
	}
	Robot::catA->moveArm(); //category A PID function
	Robot::LogNavXValues();
}
/*
 * Called once when we enter teleop mode
 */
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr){
		autonomousCommand->Cancel();
	}
	Robot::drivetrain->gearShift(1); //shift to low gear
	Robot::intake->init(); //make sure intake is not moving
	prevRBumperState = false;
	prevLBumperState = false;
	Robot::toggleIntakeOff();
	//RobotMap::intakeEncoder->Reset();
	Robot::ahrs->ZeroYaw();
	Robot::catA->portcollisLift();
	Robot::catA->initPID();
	Robot::catA->armPosinit();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run(); //make sure that we run every ~20ms
	cycleStartTime = Timer::GetFPGATimestamp();
	isFirstGather = Robot::intake->readyToShoot;
//	loadingBall = Robot::intake->loadingball;
//	Robot::intake->intakeRotateTalon2->
	//slaving the second rotate talon
	//Robot::intake->intakeRotateTalon2->Set(3);
	//SmartDashboard
	SmartDashboard::PutNumber("pot",RobotMap::pot->Get());
	SmartDashboard::PutNumber("intake pot",RobotMap::intakePot->Get());

	SmartDashboard::PutNumber("encoder dist",RobotMap::intakeEncoder->GetDistance());
	SmartDashboard::PutNumber("vel",Robot::shooter->returnVelocity());

/*
 * make sure driving works
 * test cat. A
 * test drive straight teleop
 */
	//driver controls
	if(Robot::oi->getdriveStick()->GetRawButton(XBOX::YBUTTON)){//
		Robot::catA->chivelDeFrise();
	}
	else if(Robot::oi->getdriveStick()->GetRawButton(XBOX::XBUTTON)) {
		Robot::catA->portcollisInit();
	}
	else if(Robot::oi->getdriveStick()->GetRawButton(XBOX::BBUTTON)) {
		Robot::catA->portcollisLift();
	}
	if(Robot::oi->getdriveStick()->GetRawButton(XBOX::ABUTTON)){
		//Robot::drivetrain->driveToAngle(-.8,0);
	}
	else{
		Robot::ahrs->ZeroYaw();
		//Robot::drivetrain->getDrive()->ArcadeDrive(Robot::oi->getdriveStick()->GetY(),-1*Robot::oi->getdriveStick()->GetRawAxis(4),true);
	}

	//new drive controls
	float f = Robot::oi->getdriveStick()->GetY(); //first joystick y axis
	float t = Robot::oi->getdriveStick()->GetRawAxis(4); //second joystick x axis
	double yawRate = Robot::ahrs->GetRawGyroZ() / 360.0; //scale yawRate to between -1 and 1
	SmartDashboard::PutNumber("f",f);
	SmartDashboard::PutNumber("t",t);
	SmartDashboard::PutNumber("yawRate",yawRate);
	SmartDashboard::PutNumber("raw z", Robot::ahrs->GetRawGyroZ());
	SmartDashboard::PutBoolean("is rotating", Robot::ahrs->IsRotating());

	Robot::drivetrain->newdriveSystem(f,t,yawRate);


	//tech controls

	//manual intake control
	if(Robot::oi->gettechStick()->GetRawButton(XBOX::LBUMPER)){
		Robot::shooter->shootTeleop();
	}
	if(Robot::oi->gettechStick()->GetRawButton(XBOX::RBUMPER)){
		holdingBall = false;
		loadingBall = false;
		grabbingBall = false;

		if(Robot::oi->gettechStick()->GetRawButton(XBOX::LSTICKP)){
			Robot::intake->intakeRotateTalon1->Set(-.45);
			Robot::intake->intakeRotateTalon2->Set(-.45);
			//Robot::intake->intakeSpinTalon1->Set(.65);
			//Robot::intake->intakeSpinTalon2->Set(.65);
		}
		else if(Robot::oi->gettechStick()->GetRawButton(XBOX::RSTICKP)){
			Robot::intake->intakeRotateTalon1->Set(.65);
			Robot::intake->intakeRotateTalon2->Set(.65);
			Robot::intake->intakeSpinTalon1->Set(-.65);
			Robot::intake->intakeSpinTalon2->Set(-.65);
		}
		else{
			Robot::intake->intakeRotateTalon1->Set(0);
			Robot::intake->intakeRotateTalon2->Set(0);
			Robot::intake->intakeSpinTalon1->Set(0);
			Robot::intake->intakeSpinTalon2->Set(0);
		}

	}

	if (Robot::oi->gettechStick()->GetRawButton(XBOX::BBUTTON) || holdingBall){
		toggleIntakeOff();
		holdingBall = true;
		Robot::intake->holdBall();
	}

	if(Robot::oi->gettechStick()->GetRawButton(XBOX::XBUTTON)){
		toggleIntakeOff();
		loadingBall = true;
		Robot::intake->loadingBall(cycleStartTime);
		loadStartTime = cycleStartTime;
	}

	if(Robot::intake->intakeDone){
		resetIntake();
	}
	if(Robot::oi->gettechStick()->GetRawButton(XBOX::YBUTTON) || grabbingBall){
		Robot::toggleIntakeOff();
		grabbingBall = true;
		Robot::intake->grabBall();
	}
	if(Robot::oi->gettechStick()->GetRawButton(XBOX::ABUTTON)){
		loadingBall=false;
		Robot::shooter->testPID(0);
		Robot::shooter->shooterBackTalon->SetControlMode(CANTalon::ControlMode::kVoltage);
		Robot::shooter->shooterBackTalon->Set(0);
		Robot::intake->intakeRotateTalon2->Set(0);
	}

	if(loadingBall){
		Robot::intake->loadingBall(loadStartTime);
	}

	//cat. A PID
	Robot::catA->moveArm();

	//gearshifting
	Robot::drivetrain->autoShift();

	//shooting control - not tested yet!
	Robot::shooterControl();
}
/*
 * run during test mode every 20ms - not used much
 */
void Robot::TestPeriodic() {
	lw->Run();
}
/*
 * log values from the NavX
 */
void Robot::LogNavXValues(){
	SmartDashboard::PutNumber("Angle", RobotMap::ahrs->GetAngle());
	SmartDashboard::PutNumber("Temperature (degrees celcius)", RobotMap::ahrs->GetTempC());
	SmartDashboard::PutNumber("Yaw (z axis rotation,-180 to 180)",RobotMap::ahrs->GetYaw());
}
/*
 * Log values to the fancy smart dashboard
 */
void Robot::LogHTMLDashboardValues() {
	SmartDashboard::PutNumber("CurrentGear - 1 = high", drivetrain->currentGear);
	SmartDashboard::PutNumber("encoder1",RobotMap::intakeEncoder->GetDistance());
	SmartDashboard::PutNumber("encoder2",Robot::catA->catA2->GetEncPosition());
	SmartDashboard::PutNumber("armangle",Robot::ahrs->GetYaw());
	SmartDashboard::PutNumber("shootSpeed",Robot::shooter->shooterBackTalon->GetEncVel());

}

void Robot::resetIntake(){
	isFirstGather = true;
}

void Robot::shooterControl(){
	/*
	 * new shooter control because the old one sucked
	 * Once the operator presses shoot, we start the shooter
	 * at our shoot teleop speed.  This keeps going while
	 * isShooting stays true (set by the button)
	 * We then check to see if the shooter speed is within 10% of where we want
	 * it to be, and if it is, load the ball into the shooter by running the
	 * rollers.  We then check for a voltage difference of 2 volts over the
	 * past 250ms on the shooter talons - the voltage will spike when the
	 * ball hits the shooter.  This tells us the ball has been shot, and it is
	 * okay to turn off the motors.
	 *
	 * todo: test this function!
	 */
	if(isShooting){
		Robot::shooter->shootTeleop(); //sets the shooter PID value
	}
	else{
		Robot::shooter->killShooter(); //disables PID on the shooter - better than setting to 0 because no oscillation
	}
	if(-85606 < Robot::shooter->returnVelocity() < -70824){
		Robot::intake->loadBall();
	}
	if(Robot::shooter->hasShot()){ //checks for a voltage spike
		isShooting = false;
	}
}
void Robot::toggleIntakeOff(){
	grabbingBall = false;
	loadingBall = false;
	holdingBall = false;
	secondaryHold = false;
	Robot::shooter->stopShooter();
	Robot::intake->stopIntakeSpinners();
}

START_ROBOT_CLASS(Robot);
