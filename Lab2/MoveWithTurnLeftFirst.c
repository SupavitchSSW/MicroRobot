#pragma config(Sensor, S1,     leftUltra,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     frontUltra,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S4,     rightUltra,     sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

#define baseSpeed 	35 //first test with 45
#define baseSpeedCollis 25
#define blockDistance 630 //Base 625
#define jane 1.1 //fisrt test with 1.7

#define baseLeft 		1.0 //check collis when walk
#define baseRight 	1.0 //check collis when walk
#define baseFront 	20.0//check wall in func check
#define baseWall    1.8 //check wall in func check
#define baseSpeedTurn 10
#define baseFrontCollis 7
#define wallDistance 1.8

//Jane
void checkWall();
void walkFisrtLeft();
void move_forward();
void moveUntilCollis();
void turn90left();
void turn90right();
void reset();
//J
static void displayMap();
static void DisplayBlockcount(void);
static void calPosition(void);
static void calDirection(char dirFunc);
//Field
char getMapWall(char row,char col);
char getWall(float s1,float s2,float s3);
void setMapWall(char row,char col,char wall);


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
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,2,
    3,2,2,2,2,2,2,2,6
};

char mapCountWalk[9][9]={
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0
};

task main()
{
	resetGyro(gyroSensor);
	wait1Msec(1000);
	baseDegree = getGyroDegrees(gyroSensor);

	while(1){
		walkFisrtLeft();
		displayMap();
		//DisplayBlockcount();
	}
}
//--------------------------------------------------------------------------------------
//Perfect!!
void checkWall(){
	reset();

	float left_dis  	= SensorValue(leftUltra);
	float right_dis 	= SensorValue(rightUltra);
	float front_dis 	= getUSDistance(frontUltra);

	//update map with setMapWall
	setMapWall(position[0],position[1],getWall(front_dis,right_dis,left_dis));

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
//Perfect
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

while((getMotorEncoder(leftMotor) <= blockDistance) || (getMotorEncoder(rightMotor) <= blockDistance)) {

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

		if((getMotorEncoder(leftMotor) >= blockDistance) && (getMotorEncoder(rightMotor) < blockDistance)){
			while((getMotorEncoder(rightMotor) <= blockDistance)){
				motor[leftMotor] = 0;
				motor[rightMotor] = 5;
			}

		}
		else if((getMotorEncoder(leftMotor) < blockDistance) && (getMotorEncoder(rightMotor) >= blockDistance)){
			while((getMotorEncoder(leftMotor) <= blockDistance)){
				motor[leftMotor] = 5;
				motor[rightMotor] = 0;
			}
		}//end if else

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

void reset(){
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		wait1Msec(1000);
}
//---------------------------------------------------------

// =============================== J code ==========================================

void displayMap(){
	long offsetyy = 0;
	for(long i=0;i < 9;i++)
	{
		 long offsetxx = 0;
		 for(long j=0;j < 9;j++)
		 {
		   string cat = "";
		   sprintf(cat,"%d",map[i][j]);
		   if(i == position[0] && j == position[1])displayStringAt(j+10+offsetxx,i+115-offsetyy ,"X" );
		   else displayStringAt(j+10+offsetxx,i+115-offsetyy ,cat );
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 7b19e8aabc338d3f2478255861a23cd57316b84f
	//draw current position
	eraseLine(position[0]*14,position[1]*17,position[0]*14+20,position[0]*14);
>>>>>>> 7b19e8aabc338d3f2478255861a23cd57316b84f
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


//====================================== Field code ======================


char getMapWall(char row,char col){
    return map[row][col];
}

char getWall(float s1,float s2,float s3){
    //read 3 Ultra sonic Sensor
    // s1 top | s2 right | s3 left
    char wall = 0;
    switch(direction){
    case 8://top                       || WALL ||
        if(s1 < wallDistance)wall+=8;   //top
        if(s2 < wallDistance)wall+=4;   //right
        if(s3 < wallDistance)wall+=1;   //left
        break;
    case 4://right
        if(s1 < wallDistance)wall+=4;   //right
        if(s2 < wallDistance)wall+=2;   //bottom
        if(s3 < wallDistance)wall+=8;   //top
        break;
    case 2://bottom
        if(s1 < wallDistance)wall+=2;   //bottom
        if(s2 < wallDistance)wall+=1;   //left
        if(s3 < wallDistance)wall+=4;   //right
        break;
    case 1://left
        if(s1 < wallDistance)wall+=1;   //left
        if(s2 < wallDistance)wall+=8;   //top
        if(s3 < wallDistance)wall+=2;   //bottom
    break;
    default:;
    }
    return (wall);
}
//x,y  0-8
void setMapWall(char row,char col,char wall){
    mapCountWalk[row][col] = 1;
    map[row][col] = wall | getMapWall(row,col);  //set this box
    if((wall & 8) && (row-1 >= 0 )){      //add bottom wall to top box
      char a = row-1;
    	map[a][col] = map[a][col] | 2;
    }
    if((wall & 4) && (col+1 <= 8 )){      //add left wall to right box
    	map[row][col+1] = map[row][col+1] | 1;
    }
    if((wall & 2) && (row+1 <= 8 )){      //add top wall to bottom box
      map[row+1][col] = map[row+1][col] | 8;
    }
    if((wall & 1) && (col-1 >= 0 )){      //add right wall to left box
    	char a = col-1;
      map[row][a] = map[row][a] | 4;
    }
}
