


char a[2][2]={
	1,1,
	1,1};


task main()
{
	playSound(soundBeepBeep);
	delay(1000);

	//(x,y,char)
	displayStringAt(0,6,"a");
	displayStringAt(6,6,"b");
	delay(10000);
}
