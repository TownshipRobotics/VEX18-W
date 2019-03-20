#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, 	dgtl1,  sonarDist,      sensorSONAR_inch)
#pragma config(Sensor,	I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(UART_Usage, UART1, 			uartVEXLCD, 		baudRate19200, 				IOPins, None, None)
#pragma config(Motor, 	port1,          intake,        	tmotorVex393_HBridge, openLoop)
#pragma config(Motor, 	port2,          launcherLB,    	tmotorVex393_MC29, 		openLoop)
#pragma config(Motor, 	port3,          launcherLT,    	tmotorVex393_MC29, 		openLoop)
#pragma config(Motor, 	port4,          launcherRB,    	tmotorVex393_MC29, 		openLoop)
#pragma config(Motor, 	port5,          launcherRT,    	tmotorVex393_MC29, 		openLoop)
#pragma config(Motor, 	port6,          leftFrontWheel, tmotorVex393_MC29, 		openLoop)
#pragma config(Motor, 	port7,          rightFrontWheel, tmotorVex393_MC29, 	openLoop)
#pragma config(Motor, 	port8,          rightBackWheel, tmotorVex393_MC29, 		openLoop, encoderPort, I2C_1)
#pragma config(Motor, 	port9,          leftBackWheel, 	tmotorVex393_MC29, 		openLoop)
#pragma config(Motor, 	port10,         conveyor,      	tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//variables
string distance, rotation;

// Sets launcher to a given speed
// Left bottom & right top turn clockwise, others counterclockwise
void setLauncherSpeed(int speed){
	motor[launcherLB] = speed;
	motor[launcherRT] = speed;
	motor[launcherRB] = speed;
	motor[launcherLT] = speed;
}

//turn on conveyor belt
void setConveyorSpeed(int speed){
	motor[conveyor] = speed;
}

void setWheelSpeed(int speed){
	motor[leftBackWheel] = speed;
	motor[leftFrontWheel] = speed;
	motor[rightBackWheel] = speed;
	motor[rightFrontWheel] = speed;
}

void setLeftWheels(int speed){
	motor[leftBackWheel] = speed;
	motor[leftFrontWheel] = speed;
}

void setRightWheels(int speed){
	motor[rightBackWheel] = speed;
	motor[rightFrontWheel] = speed;
}

//launches the preloaded ball
void launchOn(){
	//once speed reaches 127 leaves loop and stays
	for(int speed = 37; speed <= 127; speed += 30){
		setLauncherSpeed(speed);
		sleep(31);
	}
}

int getDistance(float tiles){
	return 392*(24*tiles)/(4*PI);
}

void moveForward(float tiles,int leftSpeed,int rightSpeed){
	resetMotorEncoder(rightBackWheel);
	setLeftWheels(leftSpeed);
	setRightWheels(rightSpeed);
	waitUntil(getMotorEncoder(rightBackWheel) >= 2100);
	setWheelSpeed(0);
}

void moveBackward(float tiles,int leftSpeed,int rightSpeed){
	resetMotorEncoder(rightBackWheel);
	setLeftWheels(leftSpeed);
	setRightWheels(rightSpeed);
	waitUntil(getMotorEncoder(rightBackWheel) <= -2100);
	setWheelSpeed(0);
}

void autonomousLauncher(){
	//******** SHOOT BALL ********
	//launch ball
	launchOn();
	//wait 1 second
	sleep(1000);
	//move up conveyor belt
	setConveyorSpeed(30);
	sleep(1500);
	//stop launcher and conveyor belt
	setLauncherSpeed(0);
	setConveyorSpeed(0);

	//******** MOVE FORWARD ********
	//move forward 1.5 tiles and stop
	moveForward(1.5,60,60);

	//******** MOVE BACKWARD ********
	//move backward 24 inches and stop
	moveBackward(1.5,-60,-60);
}

void turnRightAndPark(){
	//******** TURN ********
	//turn toward parking
		//if next to the left wall, turn right
		//if next to the right wall, turn left
	//stop wheels

	//******** GO UP PARKING SPACE ********
	//move forward onto parking space
	//stop wheels
}

void display(){
	clearLCDLine(0);
	clearLCDLine(1);
	sprintf(distance, "%d", getDistance(1.5));
	displayLCDCenteredString(0, distance);
	sprintf(rotation, "%d", getMotorEncoder(rightBackWheel));
	displayLCDCenteredString(1, rotation);
	bLCDBacklight = true;
}

task main()
{
	//******** DETERMINE WHERE YOU ARE ********
	//if next to the left wall
		//
	//if next to the right wall
		//
	//if not next to any walls
	waitUntil(vexRT[Btn8R]==1);
	display();
	autonomousLauncher();
}
