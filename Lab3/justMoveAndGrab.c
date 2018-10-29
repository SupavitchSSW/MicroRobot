#pragma config(Sensor, S1,     frontSensor,    sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     rightTrack,     sensorEV3_Color)
#pragma config(Sensor, S3,     colorCheck,     sensorLightActive)
#pragma config(Sensor, S4,     leftTrack,      sensorEV3_Color)
#pragma config(Motor,  motorA,          grabMotor,     tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//constant area
#define Kp 0.18
#define Kd 0.25
#define Kc 0.001

#define baseSpeed 40
#define turnSpeed 15
#define orangeBox 7
#define whiteTreshold 66
#define blackTreshold 20

#define baseDistance 20
#define checkColorDistance 10


// describe function
static void turnLeft(void);
static void turnRight(void);
static void stopMoving(void);
static char moveStrightTarget();
static void grab();
static void releaseGrab(void);
static void calDirection(char dirFunc);
static void calPosition(void);
static void moveAgainEncoder(void);
static void moveReverse(void);
static void moveAgainToCheckColor(void);


//global variabal
int direction = 8;
int position[2] = {8,8};
bool isDone = false ;
int rightSensor = getColorReflected(rightTrack);
int leftSensor  = getColorReflected(leftTrack);
int frontSensorValue = getUSDistance(frontSensor);
float error = rightSensor - leftSensor;
float motorSpeed = baseSpeed;
float lastError = error;
int boxColor = 2;

task main()
{
	   while(1){

     moveStrightTarget();
     moveAgainEncoder();
     turnLeft();

   }
}

void justMove(int backward){


       rightSensor = getColorReflected(rightTrack);
	     leftSensor = getColorReflected(leftTrack);
	     frontSensorValue = getUSDistance(frontSensor);

	     error = (rightSensor - leftSensor)+Kc;
       lastError = error;

       motorSpeed = Kp * error + Kd * (error - lastError);
			 wait1Msec(10);
       motor[leftMotor]  = backward*(baseSpeed - motorSpeed);
       motor[rightMotor] = backward*(baseSpeed + motorSpeed);


}

int moveStrightTarget(){

    rightSensor = getColorReflected(rightTrack);
	  leftSensor  = getColorReflected(leftTrack);
	  frontSensorValue = getUSDistance(frontSensor);
	  error = rightSensor - leftSensor;
    motorSpeed = baseSpeed;
    lastError = error;

    int box = 1;
    isDone = false ;

    // =========================  looping move and check if box ahead ==============================================
    while(!isDone){

       justMove(1);

       if(frontSensorValue <= baseDistance ){

            moveAgainToCheckColor();
            moveReverse();

            isDone = true;
            box = 0;
       }

       if(rightSensor <= 20 && leftSensor <= 20){
          isDone = true;
          calPosition();
          box = 1;
       }


    }

    stopMoving();
    return box;

}
void moveReverse(){

    while(rightSensor >= 20 && leftSensor >= 20){

       justMove(-1);

    }
    moveAgainEncoder();

}
void moveAgainToCheckColor(){

    while(frontSensorValue <= checkColorDistance){
    	 justMove(1);
    }

    int colorSensorValue = SensorValue(colorCheck);
    if(colorSensorValue >= orangeBox){
    	  boxColor = 1;
    }
    else{
    	  boxColor = 0;
    }

}
void stopMoving(){

	  motor[leftMotor] = 0 ;
	  motor[rightMotor] = 0 ;
	  delay(200);
}

void moveAgainEncoder(){
	   resetMotorEncoder(leftMotor);
	   resetMotorEncoder(rightMotor);
	   int leftdist = getMotorEncoder(leftMotor);
	   int rightdist = getMotorEncoder(rightMotor);
	   while(leftdist <= 145 && rightdist <= 145){

	     leftdist = getMotorEncoder(leftMotor);
	     rightdist = getMotorEncoder(rightMotor);
	     motor[leftMotor]  = baseSpeed ;
       motor[rightMotor] = baseSpeed ;

	   }
	   stopMoving();
}


void turnRight(){

	  int rightSensor = getColorReflected(rightTrack);
	  int leftSensor = getColorReflected(leftTrack);

	      rightSensor = getColorReflected(rightTrack);
	      leftSensor  = getColorReflected(leftTrack);
	  	  while(leftSensor >= blackTreshold ){

	          leftSensor = getColorReflected(leftTrack);
	          rightSensor = getColorReflected(rightTrack);

	  	  	  motor[rightMotor] = -turnSpeed;
	  	  	  motor[leftMotor] =  turnSpeed;

	  	  }


	  	  while(rightSensor >= blackTreshold ){

	  	  	  leftSensor = getColorReflected(leftTrack);
	          rightSensor = getColorReflected(rightTrack);

	  	  	  motor[rightMotor] = -turnSpeed;
	  	  	  motor[leftMotor] =  turnSpeed;

	  	  }


	  	  while( rightSensor <= whiteTreshold){

	  	      rightSensor = getColorReflected(rightTrack);
	          leftSensor = getColorReflected(leftTrack);

	  	      motor[rightMotor] = -turnSpeed;
	  	  	  motor[leftMotor]  =  turnSpeed;

	  	  }

	  calDirection('r');
	  stopMoving();
}

void turnLeft(){

	  int rightSensor = getColorReflected(rightTrack);
	  int leftSensor = getColorReflected(leftTrack);

	      rightSensor = getColorReflected(rightTrack);
	      leftSensor  = getColorReflected(leftTrack);
	  	  while(rightSensor >= blackTreshold ){

	          leftSensor = getColorReflected(leftTrack);
	          rightSensor = getColorReflected(rightTrack);

	  	  	  motor[rightMotor] =   turnSpeed;
	  	  	  motor[leftMotor]  =  -turnSpeed;

	  	  }


	  	  while(leftSensor >= blackTreshold ){

	  	  	  leftSensor = getColorReflected(leftTrack);
	          rightSensor = getColorReflected(rightTrack);

	  	  	  motor[rightMotor] = turnSpeed;
	  	  	  motor[leftMotor] =  -turnSpeed;

	  	  }


	  	  while( leftSensor <= whiteTreshold){

	  	      rightSensor = getColorReflected(rightTrack);
	          leftSensor = getColorReflected(leftTrack);

	  	      motor[rightMotor] = turnSpeed;
	  	  	  motor[leftMotor]  =  -turnSpeed;

	  	  }

	  calDirection('l');
	  stopMoving();
}




void grab(){


       moveMotorTarget(grabMotor,280,100);
       delay(1000);
       resetMotorEncoder(grabMotor);
}

void releaseGrab(){


       moveMotorTarget(grabMotor,-280,-100);
       delay(1000);
       resetMotorEncoder(grabMotor);

}

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
	//draw current position
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