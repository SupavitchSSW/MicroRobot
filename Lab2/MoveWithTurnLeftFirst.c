#pragma config(Sensor, S1,     leftUltra,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     frontUltra,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S4,     rightUltra,     sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

#define baseSpeed 	30 //first test with 45
#define baseSpeedCollis 25
#define blockDistance 650 //Base 625
#define jane 1.1 //fisrt test with 1.7

#define baseLeft 		0.9
#define baseRight 	0.9
#define baseFront 	20.0
#define baseWall    1.8
#define baseSpeedTurn 10
#define baseFrontCollis 7

void checkWall();
void walkFisrtLeft();
void move_forward();
void moveUntilCollis();
void turn90left();
void turn90right();
//void checkDegree();
void reset();
static void DisplayBlockcount(void);
static void calPosition(void);
static void calDirection(char dirFunc);



int leftWall=0;
int rightWall=0;
int frontWall=0;
float baseDegree;
int direction = 8;
int position[2] = {8,8};

char map[9][9]={
    9,8,8,8,8,8,8,8,12,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,2,4,
    1,0,0,0,0,0,4,15,5,
    3,2,2,2,2,2,2,10,6
};


//Use 2 sensor(left-right) for check is robot tong mai
task main()
{
	resetGyro(gyroSensor);
	wait1Msec(1000);
	baseDegree = getGyroDegrees(gyroSensor);

	while(1){
		walkFisrtLeft();
		DisplayBlockcount();
	}
}
//--------------------------------------------------------------------------------------
//Perfect!!
void checkWall(){
	reset();

	float left_dis  	= SensorValue(leftUltra);
	float right_dis 	= SensorValue(rightUltra);
	float front_dis 	= getUSDistance(frontUltra);

	//CheckLeft
	if(left_dis<=baseWall){
		leftWall=1;
		playTone(4000,30);
	}
	else{
		leftWall=0;
		playTone(4000,10);
	}
	wait1Msec(500);

	//CheckRight
	if(right_dis<=baseWall){
		rightWall=1;
		playTone(4000,30);
	}
	else{
		rightWall=0;
		playTone(4000,10);
	}
	wait1Msec(500);

	//CheckFront
	if(front_dis<=baseFront){
		frontWall=1;
		playTone(4000,30);
	}
	else{
		playTone(4000,10);
		frontWall=0;
	}
	wait1Msec(500);

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
		moveUntilCollis();
		turn90left();
		move_forward();
	}
	//1-Way have Right
	else if(leftWall==1 && rightWall==0 && frontWall==1){
		moveUntilCollis();
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
		moveUntilCollis();
		turn90left();
		move_forward();
	}
	//3-Ways
	else if(leftWall==0 && rightWall==0 && frontWall==0){
		//turn90right();
		//turn90left();
		move_forward();
	}
	//Death End
	else if(leftWall==1 && rightWall==1 && frontWall==1){
		moveUntilCollis();
		turn90left();
		turn90left();
		move_forward();
	}
	//end if-else
	//checkDegree();
}

//--------------------------------------------------------------------------------------
void move_forward(){
		reset();

		setMotorTarget(leftMotor,blockDistance,0);
		setMotorTarget(rightMotor,blockDistance,0);
		float front_dis = getUSDistance(frontUltra);

while((getMotorEncoder(leftMotor) <= blockDistance) && (getMotorEncoder(rightMotor) <= blockDistance)) {

			float left_dis  	= SensorValue(leftUltra);
			float right_dis 	= SensorValue(rightUltra);
			float front_dis 	= getUSDistance(frontUltra);


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
				degree = degree-baseDegree;
				//degree=degree/10;
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
    calPosition();
}
//--------------------------------------------------------------------------------------
//Perfect!!
void moveUntilCollis(){
		float front_dis 	= getUSDistance(frontUltra);
	while(front_dis<baseFrontCollis){
		front_dis 	= getUSDistance(frontUltra);
		motor[leftMotor] = -1*baseSpeedCollis;
		motor[rightMotor] = -1*baseSpeedCollis;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);

	while(front_dis >= baseFrontCollis){
		float left_dis  	= SensorValue(leftUltra);
		float right_dis 	= SensorValue(rightUltra);
		front_dis 	= getUSDistance(frontUltra);

		//Only Right Wall
		if(left_dis>=baseWall && right_dis<baseWall){
			float degree=baseRight-right_dis;
			motor[leftMotor] = baseSpeedCollis + (-1 * degree * jane);
			motor[rightMotor] = baseSpeedCollis + (degree * jane);
		}
		//Only Left Wall
		else if(left_dis<baseWall && right_dis>=baseWall){
			float degree=left_dis-baseLeft;
			motor[leftMotor] = baseSpeedCollis + (-1 * degree * jane);
			motor[rightMotor] = baseSpeedCollis + (degree * jane);
		}
		//Not Have Wall
		else if(left_dis>=baseWall && right_dis>=baseWall){
			float degree = getGyroDegrees(gyroSensor);
			degree = degree-baseDegree;

			motor[leftMotor] = baseSpeedCollis + (-1 * degree * jane);
			motor[rightMotor] = baseSpeedCollis + (degree * jane);
		}
		//Have Wall
		else if(left_dis<baseWall && right_dis<baseWall){
			float degree=left_dis-right_dis;
			motor[leftMotor] = baseSpeedCollis + (-1 * degree * jane);
			motor[rightMotor] = baseSpeedCollis + (degree * jane);
		}
		//End else if
	}
	//End While
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}
//--------------------------------------------------------------------------------------
void turn90left(){
	reset();

	//int degree = getGyroDegrees(gyroSensor);
	motor[leftMotor] = -20;
	motor[rightMotor] = 20;
	wait1Msec(200);
	while(baseDegree != -89){
		baseDegree = getGyroDegrees(gyroSensor);
		if(baseDegree > -89){
			 motor[leftMotor] = -10;
		   motor[rightMotor] = 10;
		}
		else if(baseDegree < -89){
			 motor[leftMotor]  = 10;
		   motor[rightMotor] = -10;
	}

}


	motor[leftMotor]  = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);

	resetGyro(gyroSensor);
	baseDegree = getGyroDegrees(gyroSensor);
	calDirection('l');

}

//--------------------------------------------------------------------------------------

void turn90right(){
	reset();

	motor[leftMotor] = 20;
	motor[rightMotor] = -20;
	wait1Msec(200);
	while(baseDegree != 88){
		baseDegree = getGyroDegrees(gyroSensor);

		if(baseDegree < 88){
			 motor[leftMotor]  = 10;
		   motor[rightMotor] =-10;
		}
		else if(baseDegree > 88){
			 motor[leftMotor]  = -10;
		   motor[rightMotor] = 10;
   	}
  }

	motor[leftMotor]  = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);
	resetGyro(gyroSensor);
	baseDegree = getGyroDegrees(gyroSensor);
	calDirection('r');
}
//--------------------------------------------------------------------------------------
//Not work
/*void checkDegree(){
	int checkDegree = getGyroDegrees(gyroSensor);
	while(checkDegree>=15 || checkDegree <= -15){
		checkDegree = getGyroDegrees(gyroSensor);
		if(checkDegree>=15){
			motor[leftMotor] = -10;
			motor[rightMotor] = 10;
		}
		else if(checkDegree <= -15){
			motor[leftMotor] = 10;
			motor[rightMotor] = -10;
		}
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}*/

//--------------------------------------------------------------------------------------
void reset(){
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		wait1Msec(1000);
}

void displayMap(){
	long offsetyy = 0;
	for(long i=0;i < 9;i++)
	{
		 long offsetxx = 0;
		 for(long j=0;j < 9;j++)
		 {
		   string cat = "";
		   sprintf(cat,"%d",map[i][j]);
		   displayStringAt(j+10+offsetxx,i+115-offsetyy ,cat );
		   offsetxx = offsetxx+17;
		 }
		 offsetyy = offsetyy+14;
	}
	 playSound(soundBeepBeep);
}

void DisplayBlockcount(){

	  delay(100);
	  eraseDisplay();
	  string str1,str2;
	  sprintf(str1,"%d",direction);
	  sprintf(str2,"(%d,%d)",position[0],position[1]);
	  displayBigTextLine(5,str1);
	  displayBigTextLine(8,str2);
	  delay(100);

}


//calculate direct
void calDirection(char dirFunc)
{
	  if(dirFunc == 'l'){
	  	 switch(direction){
	  	    case 8 :
	  	       direction = 1;
	  	       break;
	  	    case 4 :
	  	       direction = 8;
	  	       break;
	  	    case 2 :
	  	       direction = 4;
	  	       break;
	  	    case 1 :
	  	       direction = 2;
	  	       break;
	  	 }
	  }
	  else if(dirFunc == 'r'){
	  	 switch(direction){
	  	    case 8 :
	  	       direction = 4;
	  	       break;
	  	    case 4 :
	  	       direction = 2;
	  	       break;
	  	    case 2 :
	  	       direction = 1;
	  	       break;
	  	    case 1 :
	  	       direction = 8;
	  	       break;
	  	 }
	  }
}

void calPosition(){
	 switch(direction){
	   case 1 :
	      position[1]--;
	      break;
	   case 2 :
	      position[0]++;
	      break;
	   case 4 :
	      position[1]++;
	      break;
	   case 8 :
	      position[0]--;
	      break;
   }
}
