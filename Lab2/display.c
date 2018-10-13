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

static void displayMap(void);
static void DisplayBlockcount(int blockNum);


int direction = 8;
int position[2] = {8,8};


task main()
{
	playSound(soundBeepBeep);
	delay(1000);
	DisplayBlockcount(20);
	delay(10000);
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

void DisplayBlockcount(int blockNum){

	  delay(100);
	  eraseDisplay();
	  string str;
	  sprintf(str,"%d",blockNum);
	  displayBigTextLine(5,str);

}


//calculate direct
void calDirection(char dirFunc)
{
	  if(dirFunc == 'l'){
	  	 switch(direction){
	  	    case '8' :
	  	       direction = 1;
	  	       break;
	  	    case '4' :
	  	       direction = 8;
	  	       break;
	  	    case '2' :
	  	       direction = 4;
	  	       break;
	  	    case '1' :
	  	       direction = 2;
	  	       break;
	  	 }
	  }
	  else if(dirFunc == 'r'){
	  	 switch(direction){
	  	    case '8' :
	  	       direction = 4;
	  	       break;
	  	    case '4' :
	  	       direction = 2;
	  	       break;
	  	    case '2' :
	  	       direction = 1;
	  	       break;
	  	    case '1' :
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
