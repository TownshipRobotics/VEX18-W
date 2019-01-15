#pragma config(Motor,  port2,           launcherLB,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           launcherLT,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           launcherRB,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           launcherRT,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightBackWheel, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//variables
bool launcherOff = true;

//it needed to be faster so i made a slight alteration
//https://www.desmos.com/calculator/xv2hbpabjm
int modify2(int input){
	return (input+(pow(input,5)/8192-pow(input,3))/8192)/2;
}

// Sets launcher to a given speed
// Left bottom & right top turn clockwise, others counterclockwise
void setLauncherSpeed(int speed){
	motor[launcherLB] = speed;
	motor[launcherRT] = speed;
	motor[launcherRB] = -(speed);
	motor[launcherLT] = -(speed);
}

void updateWheels(){

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
