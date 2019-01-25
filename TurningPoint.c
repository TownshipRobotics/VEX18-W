#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           launcherLB,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           launcherLT,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           launcherRB,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           launcherRT,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          conveyor,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//https://www.desmos.com/calculator/xv2hbpabjm
int modJoystick(int input){
	return (input+(pow(input,5)/8192-pow(input,3))/8192)/2;
}


//************************************
//**********     WHEELS     **********
//************************************

//moves the 4 motors controlling the 4 wheels using the signals from the right and left joystick
task updateWheels(){
	while (true) {
		motor[leftFrontWheel] = modJoystick(vexRT[Ch3]);
		motor[leftBackWheel] = modJoystick(vexRT[Ch3]);
		motor[rightFrontWheel] = -(modJoystick(vexRT[Ch2]));
		motor[rightBackWheel] = -(modJoystick(vexRT[Ch2]));

		sleep(10); // To avoid a hotloop
	}
}


//************************************
//**********    LAUNCHER    **********
//************************************

// Sets launcher to a given speed
// Left bottom & right top turn clockwise, others counterclockwise
void setLauncherSpeed(int speed){
	motor[launcherLB] = speed;
	motor[launcherRT] = speed;
	motor[launcherRB] = -(speed);
	motor[launcherLT] = -(speed);
}

//gradual 37-67-97-127
//takes 124ms
void accLauncherJess(){
	//once speed reaches 127 leaves loop and stays
	for(int speed = 37; speed <= 127; speed += 30){
		setLauncherSpeed(speed);
		sleep(31);
	}
}

//61-84-105-127
//starts larger, smaller increments
//speed = 22x+61 from
//should take 100ms
void accLauncherCait(){
	for(int x = 0; x <= 3; x++){
		setLauncherSpeed(22*x+61);
		//wait 25 milliseconds
		sleep(25);
	}
}

//exponentially increases the launcher speed
//caitlin obrien
//speed = (e^x)-1 from x= 3.1 to x = 5.1
//should take 100ms
void accLauncherExp(){
	for(float x = 3.1; x <= 5.1; x+=.4){
		setLauncherSpeed(exp(x)-1);
		//waits 20 milliseconds
		sleep(20);
	}
}

// Press 8U for Jess's, 8R for Cait's, 8D for Exponential
// Press 8L to turn it off
task updateLauncher(){
	while (true) {

		// If 8U pressed, do Jess's launcher & wait for the button to be released
		if (vexRT[Btn8U] == 1){
			accLauncherJess();
			waitUntil(vexRT[Btn8U] == 0);

		// If 8R is pressed, do Cait's launcher & wait for the button to be released
		} else if (vexRT[Btn8R] == 1){
			accLauncherCait();
			waitUntil(vexRT[Btn8R] == 0);

		// If 8D is pressed, do Cait's launcher & wait for the button to be released
		} else if (vexRT[Btn8D] == 1){
			accLauncherExp();
			waitUntil(vexRT[Btn8D] == 0);

		// Otherwise make sure launcher speed is 0
		} else {
			setLauncherSpeed(0);
			sleep(10);
		}

	}
}


//************************************
//**********     INTAKE     **********
//************************************

bool intakeOff = true;

task updateIntake(){
	while(true) {

		// Check if button is pressed
		if (vexRT[Btn7L] == 1){
			if (intakeOff) {
				// Turn intake on
				intakeOff = false;

				motor[intake] = -60;
				motor[conveyor] = 60;

			} else {
				// Turn intake off
				intakeOff = true;

				motor[intake] = 0;
				motor[conveyor] = 0;

			}

			// Wait for button to be released
			waitUntil(vexRT[Btn7L] == 0);
		}

		// Sleep so that it's not a "hotloop"
		sleep(10);
	}
}



//************************************
//**********     MAIN       **********
//************************************

task main()
{
	startTask( updateWheels );
	startTask( updateLauncher );
	startTask( updateIntake );
}
