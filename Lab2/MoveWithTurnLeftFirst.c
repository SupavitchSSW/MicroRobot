#pragma config(Sensor, S1,     leftUltra,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     frontUltra,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S4,     rightUltra,     sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

#define baseSpeed 	40
#define blockDistance 625
#define jane 1.7 //fisrt test with 1.7

#define baseLeft 		0.9
#define baseRight 	0.9
#define baseFront 	20.0
#define baseWall    2.0
#define baseSpeedTurn 10

void checkWall();
void walkFisrtLeft();
void move_forward();
void turn90left();
void turn90right();
void reset();

int leftWall=0;
int rightWall=0;
int frontWall=0;

task main()
{
	while(1){
	walkFisrtLeft();
	}
}
//--------------------------------------------------------------------------------------
void checkWall(){
	reset();

	float left_dis  	= SensorValue(leftUltra);
	float right_dis 	= SensorValue(rightUltra);
	float front_dis 	= getUSDistance(frontUltra);

	//CheckLeft
	if(left_dis<=baseWall){
		leftWall=1;
		//playSound();
	}
	else
		leftWall=0;

	//CheckRight
	if(right_dis<=baseWall){
		rightWall=1;
		//playSound();
	}
	else
		rightWall=0;

	//CheckFront
	if(front_dis<=baseFront){
		frontWall=1;
		//playSound();
	}
	else
		frontWall=0;

}

//--------------------------------------------------------------------------------------
void walkFisrtLeft(){
	checkWall();

	//1-Way
	if(leftWall==1 && rightWall==1 && frontWall==0){
		move_forward();
	}
	//1-Way have Left
	else if(leftWall==0 && rightWall==1 && frontWall==1){
		turn90left();
		move_forward();
	}
	//1-Way have Right
	else if(leftWall==1 && rightWall==0 && frontWall==1){
		turn90right();
		move_forward();
	}
	//2-Ways have Left and Forward
	else if(leftWall==0 && rightWall==1 && frontWall==0){
		turn90left();
		move_forward();
	}
	//2-Ways have Right and Forward
	else if(leftWall==1 && rightWall==0 && frontWall==0){
		move_forward();
	}
	//2-Ways have Left and Right
	else if(leftWall==0 && rightWall==0 && frontWall==1){
		turn90left();
		move_forward();
	}
	//end if-else
}

//--------------------------------------------------------------------------------------
void move_forward(){
		reset();

		setMotorTarget(leftMotor,blockDistance,0);
		setMotorTarget(rightMotor,blockDistance,0);
		int baseDegree = getGyroDegrees(gyroSensor);
		float front_dis = getUSDistance(frontUltra);

while((getMotorEncoder(leftMotor) <= blockDistance) && (getMotorEncoder(rightMotor) <= blockDistance)) {

			float left_dis  	= SensorValue(leftUltra);
			float right_dis 	= SensorValue(rightUltra);
			float front_dis 	= getUSDistance(frontUltra);

			baseDegree = getGyroDegrees(gyroSensor);

			//Only Right Wall
			if(left_dis>=baseWall && right_dis<baseWall){
				float degree=baseRight-right_dis;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Only Left Wall
			else if(left_dis<baseWall && right_dis>=baseWall){
				float degree=left_dis-baseLeft;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Not Have Wall
			else if(left_dis>=baseWall && right_dis>=baseWall){
				float degree = getGyroDegrees(gyroSensor);
				degree = baseDegree-degree;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Have Wall
			else if(left_dis<baseWall && right_dis<baseWall){
				float degree=left_dis-right_dis;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}

		}//end while loop

}

//--------------------------------------------------------------------------------------
void turn90left(){
	reset();

	int degree = getGyroDegrees(gyroSensor);
	motor[leftMotor] = -10;
	motor[rightMotor] = 10;
	wait1Msec(200);
	while(degree != -89){
		degree = getGyroDegrees(gyroSensor);

		if(degree > -89){
			 motor[leftMotor] = -57;
		   motor[rightMotor] = 57;
		}
		else if(degree < -89){
			 motor[leftMotor]  = 5;
		   motor[rightMotor] = -5;
	}
}


	motor[leftMotor]  = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);

}

//--------------------------------------------------------------------------------------

void turn90right(){
	reset();

	int degree = getGyroDegrees(gyroSensor);
	motor[leftMotor] = 10;
	motor[rightMotor] = -10;
	wait1Msec(200);
	while(degree != 88){
		degree = getGyroDegrees(gyroSensor);

		if(degree < 88){
			 motor[leftMotor]  = 10;
		   motor[rightMotor] =-10;
		}
		else if(degree > 88){
			 motor[leftMotor]  = -10;
		   motor[rightMotor] = 10;
   	}
  }

	motor[leftMotor]  = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void reset(){
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		resetGyro(gyroSensor);
		wait1Msec(1000);
}
