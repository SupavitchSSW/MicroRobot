#pragma config(Sensor, S1,     leftUltra,      sensorSONAR)
#pragma config(Sensor, S2,     frontUltra,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S4,     rightUltra,     sensorSONAR)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define baseSpeed 26 //first test with 28 and 0.0885
#define baseSpeedCollis 20
#define blockDistance 630 //Base 625
float jane = 0.0738; //maybe work at 0.048 --> 0.058 --> 0.068 better work -->0.072 almost perfect -->0.0725 not ok -->0.0738 Perfect
                    //recent use 0.0894
float  janeBoth = 0.11;

#define baseFront 	20//check wall in func check
#define baseWall    18//check wall in func check
#define baseSpeedTurn 10
#define baseFrontCollis 8
#define wallDistance 18//field check wall
#define routeSize 30
#define HeapSize 30
#define stackSize 50

//Jane
void checkWall();
void walkFisrtLeft();
void move_forward();
void moveUntilCollis();
void turn90left();
void turn90right();
void setBaseLeftRightDistance();
void reset();

//J
static void displayMap(void);
static void DisplayBlockcount(void);
static void calPosition(void);
static void calDirection(char dirFunc);
static void forceToStraight(void);

//Field
void checkFrontWall();
char getMapWall(char row,char col);
char getWall(float s1,float s2,float s3);
void setMapWall(char row,char col,char wall);
void showMeDawae();
void appendHeap(char row,char col);
char isHeapEmpty();
void popHeap();
void clearHeap();
void printHeap();
void shortestPath(char targetRow,char targetCol,char startRow,char startCol);
void runShortestRoute();
void pushStack(char num);
char popStack();
char isStackEmpty();

// ======= Shortest Path
//heap
typedef struct{
    signed char next,row,col;
}Node;

Node heap[HeapSize];
char popRow=0,popCol=0,useHeap=0,createHeap=0,nextHeap=1,route[routeSize],stack[stackSize],topStack=1;

// =======


int leftWall=0;
int rightWall=0;
int frontWall=0;
float baseDegree=0;

int direction = 8;
int position[2] = {8,8};
int degreeBlock;
int baseLeft=11; //check collis when walk
int baseRight=11 ; //check collis when walk
float degree=0;
int left_dis=0;
float eiei=1;//0.78;//
int right_dis=0;
int front_dis=0;


char map[9][9]={
	  15,15,15,15,15,15,15,15,15,
	  15,15,15,15,15,15,15,15,15,
    15,9 ,10,10,8 ,10,10,12,15,
    15,5 ,15,15,5 ,15,15,5 ,15,
    15,3 ,10,8 ,2 ,10,10,4 ,15,
    15,15,15,5 ,15,15,15,3 ,12,
    15,15,15,3 ,12,15,13,15,5,
    15,15,15,15,5 ,15,5 ,15,5,
    15,15,15,11,2 ,10,2 ,10,6
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
    0,0,0,0,0,0,0,0,1

};


//test map
/*

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
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1
};
*/
task main()
{
	resetGyro(gyroSensor);
	degreeBlock = getGyroDegrees(gyroSensor);
	baseDegree = getGyroDegrees(gyroSensor);
	//setBaseLeftRightDistance();


	while(1){
 	   playSound(soundException);
	   delay(1000);
	   showMeDawae();
     delay(1000);
	   playSound(soundBeepBeep);
	   delay(1000);
	   shortestPath(8,8,4,4);
	   runShortestRoute();
}

}
//--------------------------------------------------------------------------------------

//Perfect!!
void checkWall(){
	reset();

	left_dis  	= SensorValue(leftUltra);
	right_dis 	= SensorValue(rightUltra);
	front_dis 	= getUSDistance(frontUltra);

	//update map with setMapWall
	setMapWall(position[0],position[1],getWall(front_dis,right_dis,left_dis));

	//CheckLeft
	if(left_dis<=baseWall){
		leftWall=1;
		//playTone(4000,30);
	}
	else{
		leftWall=0;
		//playTone(4000,10);
	}
	//wait1Msec(500);

	//CheckRight
	if(right_dis<=baseWall){
		rightWall=1;
		//playTone(4000,30);
	}
	else{
		rightWall=0;
	//	playTone(4000,10);
	}
	//wait1Msec(500);

	//CheckFront
	if(front_dis<=baseFront){
		frontWall=1;
		//playTone(4000,30);
	}
	else{
		//playTone(4000,10);
		frontWall=0;
	}
	//wait1Msec(500);

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
		move_forward();
	}
	//Death End
	else if(leftWall==1 && rightWall==1 && frontWall==1){
		moveUntilCollis();
		turn90left();
		moveUntilCollis();
		turn90left();
		move_forward();
	}
	//end if-else
	degreeBlock = getGyroDegrees(gyroSensor);

}

//--------------------------------------------------------------------------------------
void move_forward(){
		reset();

		setMotorTarget(leftMotor,blockDistance,0);
		setMotorTarget(rightMotor,blockDistance,0);
		front_dis = getUSDistance(frontUltra);

while((getMotorEncoder(leftMotor) <= blockDistance) || (getMotorEncoder(rightMotor) <= blockDistance)) {

			left_dis  	= SensorValue(leftUltra);
			right_dis 	= SensorValue(rightUltra);
			front_dis 	= getUSDistance(frontUltra);

      //when bot not on the right angle
      forceToStraight();

			//when bot so close to the wall
			if(left_dis <= 5 || right_dis <= 5) {
           jane = 0.5;
           janeBoth = 0.5;
       }
       else{
           jane = 0.0738;
           janeBoth = 0.11;
       }


			//Only Right Wall
			if(left_dis>=baseWall && right_dis<baseWall){
				degree=(baseRight-right_dis)*eiei;
				motor[leftMotor]  = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Only Left Wall
			else if(left_dis<baseWall && right_dis>=baseWall){
				degree=(left_dis-baseLeft)*eiei;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
				}
			//Not Have Wall
			else if(left_dis>=baseWall && right_dis>=baseWall){
				degree = getGyroDegrees(gyroSensor);
				degree = degree-((degreeBlock+baseDegree)/2);
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
				}
			//Have Wall
			else if(left_dis<baseWall && right_dis<baseWall){
				degree=(left_dis-right_dis)*eiei;//(left_dis-baseLeft)*eiei;//
				motor[leftMotor] = baseSpeed + (-1 * degree * janeBoth);
				motor[rightMotor] = baseSpeed + (degree * janeBoth);

			}
		}//end while loop

    calPosition();
}
//--------------------------------------------------------------------------------------
//Perfect!!
void moveUntilCollis(){
		front_dis 	= getUSDistance(frontUltra);
	while(front_dis<baseFrontCollis){
		front_dis 	= getUSDistance(frontUltra);
		motor[leftMotor] = -1*baseSpeedCollis;
		motor[rightMotor] = -1*baseSpeedCollis;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);

	while(front_dis >= baseFrontCollis){
		left_dis  	= SensorValue(leftUltra);
		right_dis 	= SensorValue(rightUltra);
		front_dis 	= getUSDistance(frontUltra);

	   //Only Right Wall
			if(left_dis>=baseWall && right_dis<baseWall){
				float degree=(baseRight-right_dis)*eiei;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Only Left Wall
			else if(left_dis<baseWall && right_dis>=baseWall){
				degree=(left_dis-baseLeft)*eiei;
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Not Have Wall
			else if(left_dis>=baseWall && right_dis>=baseWall){
				degree = getGyroDegrees(gyroSensor);
				degree = degree-((degreeBlock+baseDegree)/2);
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
			//Have Wall
			else if(left_dis<baseWall && right_dis<baseWall){
				degree=(left_dis-right_dis)*eiei;//(left_dis-baseLeft)*eiei;//
				motor[leftMotor] = baseSpeed + (-1 * degree * jane);
				motor[rightMotor] = baseSpeed + (degree * jane);
			}
		}//end while loop
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}
//--------------------------------------------------------------------------------------
void turn90left(){
	reset();

	//int degree = getGyroDegrees(gyroSensor);
	motor[leftMotor] = -15;
	motor[rightMotor] = 15;
	wait1Msec(200);
	while(baseDegree != -89){
		baseDegree = getGyroDegrees(gyroSensor);
		if(baseDegree > -87){
			 motor[leftMotor] = -11;
		   motor[rightMotor] = 11;
		}
		else if(baseDegree < -85){
			 motor[leftMotor]  = 3;
		   motor[rightMotor] = -3;
	}

}


	motor[leftMotor]  = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);
	setBaseLeftRightDistance();
	resetGyro(gyroSensor);
	baseDegree = getGyroDegrees(gyroSensor);
	calDirection('l');

}

//--------------------------------------------------------------------------------------

void turn90right(){
	reset();

	motor[leftMotor] = 15;
	motor[rightMotor] = -15;
	wait1Msec(200);
	while(baseDegree != 87){
		baseDegree = getGyroDegrees(gyroSensor);

		if(baseDegree < 87){
			 motor[leftMotor]  = 8;
		   motor[rightMotor] =-8;
		}
		else if(baseDegree >= 85){
			 motor[leftMotor]  = -3;
		   motor[rightMotor] = 3;
   	}
  }

	motor[leftMotor]  = 0;
	motor[rightMotor] = 0;
	wait1Msec(500);
	setBaseLeftRightDistance();
	resetGyro(gyroSensor);
	baseDegree = getGyroDegrees(gyroSensor);
	calDirection('r');
}
//--------------------------------------------------------------------------------------
void setBaseLeftRightDistance(){
	baseLeft  	= SensorValue(leftUltra);
	baseRight 	= SensorValue(rightUltra);

	if(baseLeft<7||baseLeft>11){
		baseLeft=5;
	}


	if(baseRight<7||baseRight>11){
		baseRight=5;
	}




}
//--------------------------------------------------------------------------------------

void reset(){
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
		resetMotorEncoder(leftMotor);
		resetMotorEncoder(rightMotor);
		wait1Msec(1000);
}


// ====================================== new modify area ====================================================

void forceToStraight(){
	  degree = getGyroDegrees(gyroSensor);
	  if(degree <= -13 ){

           motor[leftMotor]  = 3;
		       motor[rightMotor] = -3;
		       wait10Msec(100);
        }
        else  if(degree > 14 ){

           motor[leftMotor]  = -3;
		       motor[rightMotor] = 3;
		       wait10Msec(100);
        }
}

// =============================== J code =====================================================================

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


//====================================== Field code ======================

void checkFrontWall(){
		front_dis 	= getUSDistance(frontUltra);
		if(front_dis<=baseFront){
			moveUntilCollis();
		}
}

char getMapWall(char row,char col){
    return map[row][col];
}

char getWall(float s1,float s2,float s3){
    //read 3 Ultra sonic Sensor
    // s1 top | s2 right | s3 left
    char wall = 0;
    switch(direction){
    case 8://top                       || WALL ||
        if(s1 < baseFront)wall+=8;   //top
        if(s2 < wallDistance)wall+=4;   //right
        if(s3 < wallDistance)wall+=1;   //left
        break;
    case 4://right
        if(s1 < baseFront)wall+=4;   //right
        if(s2 < wallDistance)wall+=2;   //bottom
        if(s3 < wallDistance)wall+=8;   //top
        break;
    case 2://bottom
        if(s1 < baseFront)wall+=2;   //bottom
        if(s2 < wallDistance)wall+=1;   //left
        if(s3 < wallDistance)wall+=4;   //right
        break;
    case 1://left
        if(s1 < baseFront)wall+=1;   //left
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

void appendHeap(char row,char col){
    heap[createHeap].next = nextHeap;
    heap[createHeap].col = col;
    heap[createHeap].row = row;

    nextHeap += 1;
    createHeap += 1;
    if(nextHeap == HeapSize)
    	    nextHeap = 0;
    if(createHeap == HeapSize)
    	    createHeap = 0;
}

char isHeapEmpty(){
    if(heap[useHeap].next == -1)return 1;
    else return 0;
}

void popHeap(){
    popCol= heap[useHeap].col;
    popRow = heap[useHeap].row;
    heap[useHeap].next = -1;                   // already use
    useHeap += 1;
    if(useHeap == HeapSize)useHeap = 0;
    return ;
}

void clearHeap(){
    char i;
    for(i=0;i<HeapSize;i++){
        heap[i].next = -1;
    }

    useHeap = 0;
    createHeap = 0;
    nextHeap = 1;
    popRow = 0;
    popCol = 0;
}

void printHeap(){
    char i;
    for(i=0;i<HeapSize;i++){
        //printf("heap Row: %d Col: %d Next: %d | \n",heap[i].row,heap[i].col,heap[i].next);
    }
}

void shortestPath(char targetRow,char targetCol,char startRow,char startCol){
    char i,j,row=startRow,col=startCol;
    //printf("Start searching shortestPath \n From: %d,%d  -> %d,%d\n",startRow,startCol,targetRow,targetCol);

    typedef struct{
        char preRow,preCol,preDirection,isCheck;
    }Box;

    Box mapBox[9][9];

    //init mapNode
    for(i = 0;i<9;i++){
        for(j=0;j<9;j++){
            mapBox[i][j].isCheck = 0;
            mapBox[i][j].preRow = 0;
            mapBox[i][j].preCol = 0;
            mapBox[i][j].preDirection = 0;
        }
    }
    mapBox[startRow][startCol].isCheck = 1;

    if(startRow == targetRow && startCol == targetCol){
        //printf("\n========= route count: %d ===========\n",strlen(route));
    }else{
        do{
            //printf("search Row: %d Col: %d Wall: %d | \n",row,col,map[row][col]);
            //left
            if(((map[row][col] & 1) == 0) && (mapCountWalk[row][col-1] == 1) &&(mapBox[row][col-1].isCheck == 0)){
          //      printf("left  ");
                            //set value to next Box
                mapBox[row][col-1].isCheck = 1;
                mapBox[row][col-1].preRow = row;
                mapBox[row][col-1].preCol = col;
                mapBox[row][col-1].preDirection = 1;
                if(row == targetRow && col-1 == targetCol){
           //             printf("Found !!!\n");
                    break;
                }
                appendHeap(row,col-1);
            }
            //top
            if( ((map[row][col] & 8) == 0) && (mapCountWalk[row-1][col] == 1) && (mapBox[row-1][col].isCheck == 0)){
          //      printf("Top  ");
                //set value to next Box
                mapBox[row-1][col].isCheck = 1;
                mapBox[row-1][col].preRow = row;
                mapBox[row-1][col].preCol = col;
                mapBox[row-1][col].preDirection = 8;
                if(row-1 == targetRow && col == targetCol){
           //         printf("Found !!!\n");
                    break;
                }
                appendHeap(row-1,col);
            }
            //right
            if(((map[row][col] & 4) == 0 )&& (mapCountWalk[row][col+1] == 1 )&&( mapBox[row][col+1].isCheck == 0)){
         //       printf("right  ");
                            //set value to next Box
                mapBox[row][col+1].isCheck = 1;
                mapBox[row][col+1].preRow = row;
                mapBox[row][col+1].preCol = col;
                mapBox[row][col+1].preDirection = 4;
                if(row == targetRow && col+1 == targetCol){
           //             printf("Found !!!\n");
                    break;
                }
                appendHeap(row,col+1);
            }
            //bottom
            if(((map[row][col] & 2) == 0) && (mapCountWalk[row+1][col] == 1) && (mapBox[row+1][col].isCheck == 0)){
          //      printf("bottom  ");
                            //set value to next Box
                mapBox[row+1][col].isCheck = 1;
                mapBox[row+1][col].preRow = row;
                mapBox[row+1][col].preCol = col;
                mapBox[row+1][col].preDirection = 2;
                if(row+1 == targetRow && col == targetCol){
        //                printf("Found !!!\n");
                    break;
                }
                appendHeap(row+1,col);
            }
            if(isHeapEmpty() == 0){
                popHeap();
                row = popRow;
                col = popCol;
            }

       //     printf("\n");
        }while(1);


            //generate route
        row = targetRow;
        col = targetCol;
        char index = 0,temp;

        do{
        route[index] = mapBox[row][col].preDirection;
        temp = row;
        row = mapBox[row][col].preRow;
        col = mapBox[temp][col].preCol;
        }while(route[index++] != 0);

        //clear heap
        clearHeap();

        //print route
				/*
        for(i=0;i<index-1;i++){
            printf("%d ",route[i]);

        }*/


        index = 0;
    }


    //print searched box

    /*.
    for(i = 0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%d ",mapBox[i][j].isCheck);
        }
        printf("\n");
    }
    printf("===================\n");

    //print mapBox direction
    for(i = 0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%d ",mapBox[i][j].preDirection);
        }
        printf("\n");
    }

    */

    //return route
}

void runShortestRoute(){
    char i;

    for(i = 0;i<strlen(route);i++){
        switch(route[i]){
        case 8:                             //8 revert to 2
            if(direction == 1){
                //printf("L");
            		checkFrontWall();
                turn90left();
            }else if(direction == 8){
                //printf("LL");
								checkFrontWall();
                turn90left();
                checkFrontWall();
                turn90left();
            }else if(direction == 4){
                //printf("R");
            		checkFrontWall();
                turn90right();
            }
            //debug
            //direction = 2;

            break;
        case 4:                             //4 revert to 1
            if(direction == 8){
                //printf("L");
            	checkFrontWall();
                turn90left();
            }else if(direction == 4){
                //printf("LL");
            		checkFrontWall();
                turn90left();
                checkFrontWall();
                turn90left();
            }else if(direction == 2){
                //printf("R");
            		checkFrontWall();
                turn90right();
            }
            //debug
            //direction = 1;
            break;
        case 2:                             //2 revert to 8
            if(direction == 4){
                //printf("L");
            		checkFrontWall();
                turn90left();
            }else if(direction == 2){
                //printf("LL");
            		checkFrontWall();
                turn90left();
                checkFrontWall();
                turn90left();
            }else if(direction == 1){
                //printf("R");
								checkFrontWall();
                turn90right();
            }
            //debug
            //direction = 8;
            break;
        case 1:                             //1 revert to 4
            if(direction == 2){
                //printf("L");
            		checkFrontWall();
                turn90left();
            }else if(direction == 1){
                //printf("LL");
            		checkFrontWall();
                turn90left();
                checkFrontWall();
                turn90left();
            }else if(direction == 8){
                //printf("R");
            		checkFrontWall();
                turn90right();
            }
            //debug
            //direction = 4;
            break;
        default:;
        }
        //printf("M");
				move_forward();
				degreeBlock = getGyroDegrees(gyroSensor);
    }
    //clear route
    for(i = 0;i<routeSize;i++)route[i]=0;
    //finish
}


// ================ Search map by FIELD


void pushStack(char num){
    stack[topStack++] = num;
}

char popStack(){
    if(topStack == 0){
        return 0;
    }
    char temp = stack[--topStack];
    stack[topStack] = 0;
    return temp;
}

char isStackEmpty(){
    if(topStack == 0)return 1;
    else return 0;
}

void popStackAndRun(){
		delay(500);
		playSound(soundException);
		route[0] = popStack();
		if(route[0] != 99)runShortestRoute();
}

void showMeDawae(){
    //init stack
    stack[0] = 99;
    char canPop = 0;

    do{
    	checkWall();
    	delay(500);
    	displayMap();
    	canPop = 1;


    	if(leftWall == 0){																						// ==================== left
    		if(direction == 8){																					//left wall is 1
    			if(mapCountWalk[position[0]][position[1]-1] == 0){
    				checkFrontWall();
    				turn90left();
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(1);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 4){																		//left wall is 8
    			if(mapCountWalk[position[0]-1][position[1]] == 0){
    				checkFrontWall();
    				turn90left();
    				move_forward();
   					degreeBlock = getGyroDegrees(gyroSensor);
   					pushStack(8);
   					canPop = 0;
   					continue;
    			}
    		}
    		else if(direction == 2){																		//left wall is 4
    			if(mapCountWalk[position[0]][position[1]+1] == 0){
    				checkFrontWall();
    				turn90left();
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(4);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 1){																		//left wall is 2
    			if(mapCountWalk[position[0]+1][position[1]] == 0){
    				checkFrontWall();
    				turn90left();
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(2);
    				canPop = 0;
    				continue;
    			}
    		}
    	}
	    // ====================================================================================================

    	if(frontWall == 0){																			//========================= front
	    	if(direction == 8){																					//front wall is 8
    			if(mapCountWalk[position[0]-1][position[1]] == 0){
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(8);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 4){																		//front wall is 4
    			if(mapCountWalk[position[0]][position[1]+1] == 0){
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(4);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 2){																		//front wall is 2
    			if(mapCountWalk[position[0]+1][position[1]] == 0){
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(2);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 1){																		//front wall is 1
    			if(mapCountWalk[position[0]][position[1]-1] == 0){
    				move_forward();
    				degreeBlock = getGyroDegrees(gyroSensor);
    				pushStack(1);
    				canPop = 0;
    				continue;
    			}
    		}
	    }
	    // ====================================================================================================

	    if(rightWall == 0){
	    	if(direction == 8){																					//right wall is 4
    			if(mapCountWalk[position[0]][position[1]+1] == 0){
    				checkFrontWall();
    				turn90right();
    				move_forward();
   					degreeBlock = getGyroDegrees(gyroSensor);
   					pushStack(4);
   					canPop = 0;
   					continue;
    			}
    		}
    		else if(direction == 4){																		//right wall is 2
    			if(mapCountWalk[position[0]+1][position[1]] == 0){
    				checkFrontWall();
    				turn90right();
    				move_forward();
   					degreeBlock = getGyroDegrees(gyroSensor);
   					pushStack(2);
   					canPop = 0;
   					continue;
    			}
    		}
    		else if(direction == 2){																		//right wall is 1
    			if(mapCountWalk[position[0]][position[1]-1] == 0){
    				checkFrontWall();
    				turn90right();
    				move_forward();
   					degreeBlock = getGyroDegrees(gyroSensor);
   					pushStack(1);
   					canPop = 0;
   					continue;
    			}
    		}
    		else if(direction == 1){																		//right wall is 8
    			if(mapCountWalk[position[0]-1][position[1]] == 0){
    				checkFrontWall();
    				turn90right();
    				move_forward();
   					degreeBlock = getGyroDegrees(gyroSensor);
   					pushStack(8);
   					canPop = 0;
   					continue;
    			}
    		}
	    }

	    if(canPop)popStackAndRun();

    }while(!isStackEmpty());
}
