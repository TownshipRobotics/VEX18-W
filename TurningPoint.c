#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           launcherLB,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           launcherLT,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           launcherRB,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           launcherRT,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           wheelLF,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           wheelLB,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           wheelRF,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           wheelRB,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          conveyor,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//variables
bool launcherOff = true;

bool launcherOn = false;

//https://www.desmos.com/calculator/xv2hbpabjm
int modJoystick(int input){
	return (input+(pow(input,5)/8192-pow(input,3))/8192)/2;
}

//moves the 4 motors controlling the 4 wheels using the signals from the right and left joystick
void updateWheels(){
	motor[wheelLF] = modJoystick(vexRT[Ch3]);
	motor[wheelLB] = modJoystick(vexRT[Ch3]);
	motor[wheelRF] = modJoystick(vexRT[Ch2]);
	motor[wheelRB] = modJoystick(vexRT[Ch2]);
}

// Sets launcher to a given speed
// Left bottom & right top turn clockwise, others counterclockwise
void setLauncherSpeed(int speed){
	motor[launcherLB] = speed;
	motor[launcherRT] = speed;
	motor[launcherRB] = -(speed);
	motor[launcherLT] = -(speed);
}

void updateLauncher(){
	if (vexRT[Btn8L] == 1) {
		if (! launcherOn) {
			// Do the acceleration
			// Turn on conveyor
			launcherOn = true;
		}
	} else {
		// Turn off conveyor
		setLauncherSpeed(0);
		launcherOn = false;
	}
}

//gradual 37-67-97-127
//takes 124ms
void updateLauncherJess(){
	//if the button is being pressed
	if(vexRT[Btn8U] == 1){
		if(launcherOff){
			launcherOff = false;
			//once speed reaches 127 leaves loop and stays
			for(int speed = 37; speed <= 127; speed += 30){
				setLauncherSpeed(speed);
				sleep(31);
			}
		} else { // if launcher is on, turn off
			launcherOff = true;
			setLauncherSpeed(0);
		}
	}
}

//61-84-105-127
//starts larger, smaller increments
//speed = 22x+61 from
//should take 100ms
void updateLauncherCait(){
	//if button 8R is pressed
	if(vexRT[Btn8R] == 1){
		//if launcher is off, turn on
		if(launcherOff){
			launcherOff = false;
			//starts at 61 and accelerates to 127
			for(int x = 0; x <= 3; x++){
				setLauncherSpeed(22*x+61);
				//wait 25 milliseconds
				sleep(25);
			}
		} else { //if launcher is on, turn off
			launcherOff = true;
			setLauncherSpeed(0);
		}
	}
}

//exponentially increases the launcher speed
//caitlin obrien
//speed = (e^x)-1 from x= 3.1 to x = 5.1
//should take 100ms
void updateLauncherExponential(){
	//if button 8D is pressed
	if(vexRT[Btn8D] == 1){
		//if the launcher is off, turn on
		if(launcherOff){
			launcherOff = false;
			//starts at 21 and accelerates to 163
			for(float x = 3.1; x <= 5.1; x+=.4){
				setLauncherSpeed(exp(x)-1);
				//waits 20 milliseconds
				sleep(20);
			}
		}
		//if the launcher is on, turn off motors
		else{
			launcherOff = true;
			setLauncherSpeed(0);
		}
	}
}

task main()
{
	while(true){
		updateWheels();
		updateLauncherJess();
		updateLauncherCait();
		updateLauncherExponential();
	}

}
