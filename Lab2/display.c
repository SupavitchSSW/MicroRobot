#define offsetx 5
#define offsety 5

char a[2][2]={
	1,2,
	4,8 };

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

task main()
{
	playSound(soundBeepBeep);
	delay(1000);
	//(x,y,char)
	displayMap();
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
