#pragma config(Sensor, in1,    selector,       sensorAnalog)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           backLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port3,           rightLift1,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,           rightLift2,    tmotorVex393, openLoop)
#pragma config(Motor,  port5,           liftClaw2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           liftClaw1,     tmotorVex393, openLoop)
#pragma config(Motor,  port7,           leftLift2,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,           leftLift1,     tmotorVex393, openLoop)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          backRight,     tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*TODO:

1. Replace repeated code with functions if possible
2. Write encoder functions
3. make sure functions are consitent
4. Add lateral move for time and distance
5. Move actual automonous to a seperate file
6. Make time functions actual go for Seconds rather than milis (multiple 1msec by 1000)

*/

void waitForTruth(bool truth){
	while(!truth){
		wait1Msec(1);
	}

}

//linear:  straight  forward, backward in any direction
void linearMove(int power){
	LEFT_BACK =	power;
	RIGHT_BACK = power;
	LEFT_FRONT = power;
	RIGHT_FRONT = power;
	wait1Msec(1000);
}

//lift arm function for the robot
void liftArm(const string direction, int power, int time) {
	if(direction == "up") {
		RIGHT_LIFT_MOTOR1 = -power;
		RIGHT_LIFT_MOTOR2 = -power;
		LEFT_LIFT_MOTOR1 = -power;
		LEFT_LIFT_MOTOR2 = -power;
	}
	if(direction == "down") {
		RIGHT_LIFT_MOTOR1 = -power;
		RIGHT_LIFT_MOTOR2 = -power;
		LEFT_LIFT_MOTOR1 = -power;
		LEFT_LIFT_MOTOR2 = -power;
	}
	wait1Msec(time);
	RIGHT_LIFT_MOTOR1 = 0;
	RIGHT_LIFT_MOTOR2 = 0;
	LEFT_LIFT_MOTOR1 = 0;
	LEFT_LIFT_MOTOR2 = 0;
}

//lift claw function for the claw
void controlClaw(const string direction, int power, int time) {
	if(direction == "up") {
		LIFT_CLAW_MOTOR1  = power;
		LIFT_CLAW_MOTOR2 = power;
	}
	if(direction == "down") {
		LIFT_CLAW_MOTOR1  = -power;
		LIFT_CLAW_MOTOR2  = -power;
	}
	wait1Msec(time);
	LIFT_CLAW_MOTOR1 = 0;
	LIFT_CLAW_MOTOR2 = 0;
}

//lateral move will decide in which direction the robot will go(left and right)
void lateralMove(const string direction, int power) {
	if(direction == "left") {
		LEFT_FRONT = power;
		LEFT_BACK = -power;
		RIGHT_FRONT = -power;
		RIGHT_BACK = power;
	}
	if(direction == "right") {
		LEFT_FRONT = -power;
		LEFT_BACK = power;
		RIGHT_FRONT = power;
		RIGHT_BACK = -power;
	}
	linearMove(0);
}

void turnInPlace(const string direction, int power){
	if(direction == "right"){
		LEFT_FRONT = -power;
		LEFT_BACK = power;
		RIGHT_FRONT = power;
		RIGHT_BACK = -power;
	}
	if (direction ==  "left") {
		LEFT_BACK =	-power;
		RIGHT_BACK = power;
		LEFT_FRONT = power;
		RIGHT_FRONT = -power;
	}

}

void forwardTime(int power, int mSecs) {
	linearMove(power);
	wait1Msec(mSecs);
	linearMove(0);
}

void backwardTime(int power, int mSecs) {
	linearMove(-power);
	wait1Msec(mSecs);
	linearMove(0);
}

void leftMoveTime(int power, int mSecs) {
	lateralMove("left", power);
	wait1Msec(mSecs);
	linearMove(0);
}

void rightMoveTime(int power, int mSecs) {
	lateralMove("right", power);
	wait1Msec(mSecs);
	linearMove(0);
}


void turnForSeconds(const string direction, float seconds, int power){

	if(direction == "right") {
		LEFT_BACK = -power;
		LEFT_FRONT = -power;
		RIGHT_FRONT = power;
		RIGHT_BACK = power;
	}
	else if(direction == "left") {
		LEFT_BACK = power;
		LEFT_FRONT = power;
		RIGHT_FRONT = -power;
		RIGHT_BACK = -power;
	}
}

void moveInLineForSeconds(const string direction, int power){

}



void turnAmount(const string direction, float amount, int power){
	turnInPlace(direction, power);
	if(direction == "left"){
		waitForTruth(SensorValue[rightEncoder] >= amount && SensorValue[leftEncoder] <= -amount);
		} else {
		waitForTruth(SensorValue[rightEncoder] <= -amount && SensorValue[leftEncoder] >= amount);
	}
LEFT_FRONT = 0;
LEFT_BACK = 0;
RIGHT_FRONT = 0;
RIGHT_BACK = 0;
}

void forwardDistance(int power, float amount){
	linearMove(power);
waitForTruth(SensorValue[rightEncoder] >= amount && SensorValue[leftEncoder] >= amount);
}

void forwardExact(int power, float amount, int timeCap){
LEFT_FRONT = power - (SensorValue[leftEncoder] - amount);
LEFT_BACK = power - (SensorValue[leftEncoder] - amount);
RIGHT_FRONT = power - (SensorValue[rightEncoder] - amount);
RIGHT_BACK = power - (SensorValue[rightEncoder] - amount);
wait1Msec(timeCap);
LEFT_FRONT = 0;
LEFT_BACK = 0;
RIGHT_FRONT = 0;
RIGHT_BACK = 0;
}



//Autonomous Programs

void blueRight(){
forwardExact(50, 100, 1500);
controlClaw("up", 50, 500);
turnAmount("right", 50, 100);
forwardExact(50, 75, 1000);
controlClaw("up", 50, 500);
backwardTime(50,500);
}

void blueLeft(){

}

void redRight(){

}

void redLeft(){
	blueRight();
}

void challenge(){

}
