#include <stdio.h>
//Jane
void mergeBox();
int findNearBox(int positionX,int positionY);
void grabNearBox();
void deleteMark();
void setPosition();
void test();
void turnLeft();
void turnRight();
void printMap();
void dropNearBox();
void setBox();
void findIndex(int positionX,int positionY);
int box=41;
int littleBox=2;

//field
#define wallDistance 18
#define routeSize 50
#define HeapSize 50
#define stackSize 70

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
int shortestPath(char targetRow,char targetCol,char startRow,char startCol);
int runShortestRoute();
void pushStack(char num);
char popStack(void);
char isStackEmpty(void);
int showMeDabox();
void printMapCountWalk();
int searchNext();
int dropYourBox(char t_row,char t_col,char size);
int decodeRoute();
int checkShortestRoute();
void addRouteCode(char c,int n);
int moveForwardTemp();
int checkTurnRight(char row,char col,char d);
int checkTurnLeft(char row,char col,char d);
int shortestPathV2(char targetRow,char targetCol,char startRow,char startCol);
// ======= Shortest Path
//heap
typedef struct{
    signed char next,row,col;
}Node;

Node heap[HeapSize];
char popRow=0,popCol=0,useHeap=0,createHeap=0,nextHeap=1,route[routeSize],routeCode[routeSize],routeCodeIndex=0,stack[stackSize],topStack=1,countShortestPathBlock=0,direction=8,countBox=0;
char position[2]={9,9},searchTarget[2]={8,9},positionTemp[2],directionTemp=8;

//Jane variable
int X=9,Y=9;
int min=100,minX=0,minY=0,minBox=0,checkMinBox=1000;
int mark[5][2];
//*****************************************
//color
//black=40 orange=41
int black=40,orange=41;
//grab1Box '^'=8 'v'=2 '>'= 4 '<' = 1
int grab1BoxUP=8 ,grab1BoxDOWN=2 ,grab1BoxRIGHT=4 ,grab1BoxLEFT=1;
//drop1Box '^'=18 'v'=12 '>'=14 '<' =11
int grab2BoxUP=18,grab2BoxDOWN=12,grab2BoxRIGHT=14,grab2BoxLEFT=11;
//grab2Box '^'=28 'v'=22 '>'=24 '<' =21
int drop1BoxUP=28,drop1BoxDOWN=22,drop1BoxRIGHT=24,drop1BoxLEFT=21;
//drop2Box '^'=38 'v'=32 '>'=34 '<' =31
int drop2BoxUP=38,drop2BoxDOWN=32,drop2BoxRIGHT=34,drop2BoxLEFT=31;
//*****************************************
//Not have Box

/*char map[10][10]={
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,40 ,0 ,21,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,40,0 ,41,0 ,0 ,40,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,32,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,41,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,41,0 ,0 ,
    0 ,0 ,21,0 ,0 ,0 ,38,40,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,41,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
};

char mapCountWalk[10][10]={
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,0,1,0,1,1,0,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,1,1,
    1,1,1,1,1,1,1,0,1,1,
    1,1,1,1,1,1,1,0,1,1,
    1,1,1,1,1,0,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1
};*/

char map[10][10]={
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,21,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,32,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,21,0 ,0 ,0 ,38,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
};

char mapCountWalk[10][10]={
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1
};

char mapBlockTurn[10][10]={
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1
};



void main(){
    showMeDabox();
    //printMap();
    //shortestPath(1,7,7,2);
    //generate 2box and mark

    for(int i =0;i<3;i++){
        printMap();
        printMapCountWalk();
        mergeBox();
        printMap();
        printMapCountWalk();
        printf("Position of ROBOT: %d %d",position[0],position[1]);
        printf("\n=====================\n FIELD code  INPUT number 1 for move each step \n======================\n");
        printf("\n=====================\n Find Near Box \n======================\n");
        findNearBox(position[0],position[1]);
        printMapCountWalk();
        printf("\n=====================\n Start GRAP \n======================\n");
        grabNearBox();
        printMapCountWalk();
        printf("\n position of ROBOT: %d %d",position[0],position[1]);
        //whit Box is?
        if (littleBox==0){
            box=42;
        }
        printf("\n=====================\n finish run grab NearBox \n======================\n");
        printf("\n position of ROBOT: %d %d",position[0],position[1]);
        printMap();
        printMapCountWalk();
        printf("\n=====================\n run find Index \n======================\n");
        findIndex(position[0],position[1]);
        printf("\n<3 position of ROBOT: %d %d\n",position[0],position[1]);
        //dropNearBox();

        dropYourBox(minX,minY,box);
        setBox();
        printf("\n=====================\n finish run find Index \n======================\n");
        printMap();
        printMapCountWalk();
    }
}
//====================================== Jane Code =======================
//Perfect!!
void mergeBox(){
    for(int i=1;i<X;i++){
        for(int j=1;j<Y;j++){
            if(map[i][j]==orange){
                //one Box check around Box
                if(map[i-1][j]!=orange && map[i+1][j]!=orange && map[i][j-1]!=orange && map[i][j+1]!=orange){
                    //Top of Box
                    if(map[i-1][j]!=orange && map[i-1][j]!=black && map[i-1][j]<20){
                        map[i-1][j]=grab1BoxDOWN;
                    }
                    //Buttom of Box
                    if(map[i+1][j]!=orange && map[i+1][j]!=black && map[i+1][j]<20){
                        map[i+1][j]=grab1BoxUP;
                    }
                    //Left of Box
                    if(map[i][j-1]!=orange && map[i][j-1]!=black && map[i][j-1]<20){
                        map[i][j-1]=grab1BoxRIGHT;
                    }
                    //Right of Box
                    if(map[i][j+1]!=orange && map[i][j+1]!=black && map[i][j+1]<20){
                        map[i][j+1]=grab1BoxLEFT;
                    }
                }//End if check around 1 Box

                //two Box check Box
                else{
                    //Box in Column
                    if((map[i-1][j]==orange)||map[i+1][j]==orange){
                        //UP
                        if(map[i-1][j]==orange){
                            map[i][j]=42;
                            map[i-1][j]=42;
                            if(map[i-2][j]!=black && map[i-2][j]<20){
                                map[i-2][j]=grab2BoxDOWN;
                            }
                            if(map[i+1][j]!=black && map[i+1][j]<20){
                                map[i+1][j]=grab2BoxUP;
                            }
                        }
                        //DOWN
                        else if(map[i+1][j]==orange){
                            map[i][j]=42;
                            map[i+1][j]=42;
                            if(map[i+2][j]!=black && map[i+2][j]<20){
                                map[i+2][j]=grab2BoxUP;
                            }
                            if(map[i-1][j]!=black && map[i-1][j]<20){
                                map[i-1][j]=grab2BoxDOWN;
                            }
                        }

                    }//End if Box in Column

                    //Box in Row
                    if((map[i][j-1]==orange)||(map[i][j+1]==orange)){
                        //LEFT
                        if(map[i][j-1]==orange){
                            map[i][j]=42;
                            map[i][j-1]=42;
                            if(map[i][j-2]!=black && map[i][j-2]<20){
                                map[i][j-2]=grab2BoxRIGHT;
                            }
                            if(map[i][j+1]!=black && map[i][j+1]<20){
                                map[i][j+1]=grab2BoxLEFT;
                            }
                        }
                        //RIGHT
                        if(map[i][j+1]==orange){
                            map[i][j]=42;
                            map[i][j+1]=42;
                            if(map[i][j-1]!=black && map[i][j-1]<20){
                                map[i][j-1]=grab2BoxRIGHT;
                            }
                            if(map[i][j+2]!=black && map[i][j+2]<20){
                                map[i][j+2]=grab2BoxLEFT;
                            }
                        }
                    }//End if Box in Row
                }//End if check 2 Box
            // for(int i=0;i<10;i++){
            //     for(int j=0;j<10;j++){
            //         printf("%d ",map[i][j]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");

            }//End if check IS Box


        }//End for J
    }//End for I

}
//Little Box OK
int findNearBox(int positionX,int positionY){
    //find NEAR box
    min=1000;

    //little box first
    if(littleBox!=0){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if((map[i][j] >= grab1BoxLEFT ) && (map[i][j]<grab2BoxLEFT)){
                    if((((positionX-i)*(positionX-i))+((positionY-j)*(positionY-j)))<=min){
                        searchTarget[0]=i;
                        searchTarget[1]=j;
                        minX=i;
                        minY=j;
                        min=(((positionX-i)*(positionX-i))+((positionY-j)*(positionY-j)));
                        printf("== FIND Little Box ==\ndirection:%d .\nlittle box in map : minX=%d minY=%d. \nDistance is: %d\nRobot position[%d,%d] , Robot direction %d\n",map[minX][minY],searchTarget[0],searchTarget[1],min,position[0],position[1],direction);
                    }
                }
            }
        }//END find NEAR box
    }
    // create for big box
    if(littleBox==0){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if((map[i][j] >= grab2BoxLEFT ) && (map[i][j]<drop1BoxLEFT)){
                    if((((positionX-i)*(positionX-i))+((positionY-j)*(positionY-j)))<=min){
                        searchTarget[0]=i;
                        searchTarget[1]=j;
                        minX=i;
                        minY=j;
                        min=(((positionX-i)*(positionX-i))+((positionY-j)*(positionY-j)));
                        printf("== FIND Big Box ==\ndirection:%d .\nBIG box in map : minX=%d minY=%d. \nDistance is: %d\n",map[minX][minY],searchTarget[0],searchTarget[1],min);
                    }
                }
            }
        }//END find NEAR box
    }    //printf("near pos is (%d , %d)\n",minX,minY);
}
//Insert GRAB
void findIndex(int positionX,int positionY){
//find Index
    min=10000;

    //little box first
    if(littleBox!=0){
        printf("EIEI %d",littleBox);
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(map[i][j]==drop1BoxLEFT ){
                    printf("dropBOX");
                    if((((positionX-i)*(positionX-i))+((positionY-j)*(positionY-j)))<=min){
                       printf("FoundDropBOX");
                        searchTarget[0]=i;
                        searchTarget[1]=j;
                        minX=i;
                        minY=j;
                        min=(((positionX-i)*(positionX-i))+((positionY-j)*(positionY-j)));
                        printf("== FIND Little INDEX ==\ndirection:%d .\nlittle INDEX in map : minX=%d minY=%d. \nDistance is: %d\n",map[minX][minY],searchTarget[0],searchTarget[1],min);

                    }
                }
            }
        }//END find NEAR box
    }
    // create for big box
    else if(littleBox==0){
        minBox=0;
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(map[i][j]>=drop2BoxLEFT && map[i][j]<= drop2BoxUP){
                        //TOP
                        if(map[i][j]!=black && map[i][j]!=orange){
                            if(map[i][j]==drop2BoxDOWN){

                                if(mapCountWalk[i][j-1]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i][j+1]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i+1][j-1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i+1][j+1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i-1][j-1]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i-1][j]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i-1][j+1]==0){
                                    minBox=minBox+1;
                                }
                                //============================
                                if(minBox<=checkMinBox){
                                    minX=i;
                                    minY=j;
                                    searchTarget[0]=i;
                                    searchTarget[1]=j;
                                    checkMinBox=minBox;

                                }
                            }
                            //BUTTOM
                            else if(map[i][j]==drop2BoxUP){
                                if(mapCountWalk[i][j+1]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i][j-1]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i-1][j-1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i-1][j+1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i+1][j-1]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i+1][j]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i+1][j+1]==0){
                                    minBox=minBox+1;
                                }
                                //============================
                                if(minBox<=checkMinBox){
                                    minX=i;
                                    minY=j;
                                    searchTarget[0]=i;
                                    searchTarget[1]=j;
                                    checkMinBox=minBox;

                                }
                            }
                            //RIGHT
                            else if(map[i][j]==drop2BoxLEFT){
                                if(mapCountWalk[i-1][j]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i+1][j]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i-1][j-1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i+1][j-1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i-1][j+1]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i][j+1]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i+1][j+1]==0){
                                    minBox=minBox+1;
                                }
                                //============================
                                if(minBox<=checkMinBox){
                                    minX=i;
                                    minY=j;
                                    searchTarget[0]=i;
                                    searchTarget[1]=j;
                                    checkMinBox=minBox;

                                }
                            }
                            //LEFT
                            else if(map[i][j]==drop2BoxRIGHT){
                                if(mapCountWalk[i-1][j]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i+1][j]==0){
                                    minBox=minBox+3;
                                }
                                else if(mapCountWalk[i-1][j+1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i+1][j+1]==0){
                                    minBox=minBox+2;
                                }
                                else if(mapCountWalk[i-1][j-1]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i][j-1]==0){
                                    minBox=minBox+1;
                                }
                                else if(mapCountWalk[i+1][j-1]==0){
                                    minBox=minBox+1;
                                }

                                //============================
                                if(minBox<=checkMinBox){
                                    minX=i;
                                    minY=j;
                                    searchTarget[0]=i;
                                    searchTarget[1]=j;
                                    checkMinBox=minBox;

                                }
                            }
                        }

                }
            }
        }
        printf("== FIND BIG INDEX ==\ndirection:%d .\nBIG INDEX in map : minX=%d minY=%d. \nDistance is: %d\n",map[minX][minY],searchTarget[0],searchTarget[1],min);


    }
    //printf("near pos is (%d , %d)\n",minX,minY);
}

void grabNearBox(){
    shortestPath(position[0],position[1],searchTarget[0],searchTarget[1]);
    printf("\n >>>>>>>>>>>>>>>>> grab Route <<<<<<<<<<<<<<");
    for(int i = 0;i<strlen(route);i++)printf("%d",route[i]);
    runShortestRoute();
    turnRobotToBox();
    //grab
    deleteMark();

}

void dropNearBox(){
    shortestPath(position[0],position[1],searchTarget[0],searchTarget[1]);
    runShortestRoute();
    if(littleBox!=0){
    turnRobotToBox();
    }
    //Drop
    setBox();

}
void setBox(){
    if(littleBox!=0){
        mapCountWalk[minX][minY]=0;
        map[minX][minY]=40;
        littleBox=littleBox-1;
    }
}
void setPosition(){
    //position[0]=minX;
    //position[1]=minY;
    map[position[0]][position[1]]='X';
    printMap();
}
void turnRobotToBox(){
    //direction Robot is UP
    if(direction==8){
        //TOP of box target
        if((map[minX][minY]%10)==2){
            turnLeft();
            turnLeft();
            //grap
        }
        //Buttom of box target
        else if((map[minX][minY]%10)==8){
            //grap
        }
        //Left of box target
        else if((map[minX][minY]%10)==4){
            turnRight();
            //grap
        }
        //Right of box target
        else if((map[minX][minY]%10)==1){
            turnLeft();
            //grap
        }
    }
    //direction Robot is DOWN
    else if(direction==2){
        //TOP of box target
        if((map[minX][minY]%10)==2){
            //grap
        }
        //Buttom of box target
        else if((map[minX][minY]%10)==8){
            turnRight();
            turnRight();
            //grap
        }
        //Left of box target
        else if((map[minX][minY]%10)==4){
            turnLeft();
            //grap
        }
        //Right of box target
        else if((map[minX][minY]%10)==1){
            turnRight();
        }
    }
    //direction Robot is LEFT
    else if(direction==1){
        //TOP of box target
        if((map[minX][minY]%10)==2){
            turnLeft();
            //grap
        }
        //Buttom of box target
        else if((map[minX][minY]%10)==8){
            turnRight();
            //grap
        }
        //Left of box target
        else if((map[minX][minY]%10)==4){
            turnRight();
            turnRight();
            //grap
        }
        //Right of box target
        else if((map[minX][minY]%10)==1){
            //grap
        }
    }
    //direction Robot is RIGHT
    else if(direction==4){
        //TOP of box target
        if((map[minX][minY]%10)==2){
            turnRight();
            //grap
        }
        //Buttom of box target
        else if((map[minX][minY]%10)==8){
            turnLeft();
            //grap
        }
        //Left of box target
        else if((map[minX][minY]%10)==4){
            //grap
        }
        //Right of box target
        else if((map[minX][minY]%10)==1){
            turnRight();
            turnRight();
            //grap
        }
    }
}

void deleteMark(){
    //1 Box
    if(map[position[0]][position[1]]>=grab1BoxLEFT && map[position[0]][position[1]]<grab2BoxLEFT){
        //TOP
        if(map[position[0]+1][position[1]]==orange){

            mark[0][0]= position[0]+1; mark[0][1]= position[1]   ;
            mark[1][0]= position[0]+1; mark[1][1]= position[1]-1 ;
            mark[2][0]= position[0]+1; mark[2][1]= position[1]+1 ;
            mark[3][0]= position[0]+2; mark[3][1]= position[1]   ;
            mark[4][0]= position[0]  ; mark[4][1]= position[1]   ;

            mapCountWalk[position[0]+1][position[1]]= 1;
            map[position[0]+1][position[1]]=0;
        }
        //RIGHT
        else if(map[position[0]][position[1]-1]==orange){

            mark[0][0]= position[0]; mark[0][1]= position[1]-2 ;
            mark[1][0]= position[0]; mark[1][1]= position[1] -1;
            mark[2][0]= position[0]; mark[2][1]= position[1] ;
            mark[3][0]= position[0]+1; mark[3][1]= position[1]-1 ;
            mark[4][0]= position[0]-1; mark[4][1]= position[1]-1;

            mapCountWalk[position[0]][position[1]-1]= 1;
            map[position[0]][position[1]-1]=0;
        }
        //LEFT
        else if(map[position[0]][position[1]+1]==orange){
            mark[0][0]= position[0]; mark[0][1]= position[1] ;
            mark[1][0]= position[0]; mark[1][1]= position[1]+1 ;
            mark[2][0]= position[0]; mark[2][1]= position[1]+2 ;
            mark[3][0]= position[0]-1; mark[3][1]= position[1]+1 ;
            mark[4][0]= position[0]+1; mark[4][1]= position[1]+1 ;

            mapCountWalk[position[0]][position[1]+1]= 1;
            map[position[0]][position[1]+1]=0;
        }
        //DOWN
        else if(map[position[0]-1][position[1]]==orange){
            mark[0][0]= position[0]; mark[0][1]= position[1] ;
            mark[1][0]= position[0]-1; mark[1][1]= position[1] ;
            mark[2][0]= position[0]-2; mark[2][1]= position[1] ;
            mark[3][0]= position[0]-1; mark[3][1]= position[1]-1 ;
            mark[4][0]= position[0]-1; mark[4][1]= position[1]+1 ;

            mapCountWalk[position[0]-1][position[1]]= 1;
            map[position[0]-1][position[1]]=0;
        }

        for(int i=0;i<5;i++){
            if(map[mark[i][0]][mark[i][1]]<drop1BoxLEFT){
                map[mark[i][0]][mark[i][1]]=0;
            }

        }

    }

    //2 Box
    if(map[position[0]][position[1]]>=grab2BoxLEFT&&map[position[0]][position[1]]<drop1BoxLEFT){
        if(map[position[0]][position[1]] == grab2BoxDOWN){
            mark[0][0]= position[0]; mark[0][1]= position[1] ;
            mark[1][0]= position[0]+1; mark[1][1]= position[1] ;
            mark[2][0]= position[0]+2; mark[2][1]= position[1] ;
            mark[3][0]= position[0]+3; mark[3][1]= position[1] ;

            mapCountWalk[position[0]+1][position[1]]=1;
            mapCountWalk[position[0]+2][position[1]]=1;
            map[position[0]+1][position[1]]=0;
            map[position[0]+2][position[1]]=0;
        }
        else if(map[position[0]][position[1]] == grab2BoxUP){
            mark[0][0]= position[0]; mark[0][1]= position[1] ;
            mark[1][0]= position[0]-1; mark[1][1]= position[1] ;
            mark[2][0]= position[0]-2; mark[2][1]= position[1] ;
            mark[3][0]= position[0]-3; mark[3][1]= position[1] ;

            mapCountWalk[position[0]-1][position[1]]=1;
            mapCountWalk[position[0]-2][position[1]]=1;
            map[position[0]-1][position[1]]=0;
            map[position[0]-2][position[1]]=0;
        }
        else if(map[position[0]][position[1]] == grab2BoxRIGHT){
            mark[0][0]= position[0]; mark[0][1]= position[1] ;
            mark[1][0]= position[0]; mark[1][1]= position[1]+1 ;
            mark[2][0]= position[0]; mark[2][1]= position[1]+2;
            mark[3][0]= position[0]; mark[3][1]= position[1]+3 ;

            mapCountWalk[position[0]][position[1]+1]=1;
            mapCountWalk[position[0]][position[1]+2]=1;
            map[position[0]][position[1]+1]=0;
            map[position[0]][position[1]+2]=0;
        }
        else if(map[position[0]][position[1]] == grab2BoxLEFT){
            mark[0][0]= position[0]; mark[0][1]= position[1] ;
            mark[1][0]= position[0]; mark[1][1]= position[1]-1 ;
            mark[2][0]= position[0]; mark[2][1]= position[1]-2 ;
            mark[3][0]= position[0]; mark[3][1]= position[1]-3 ;

            mapCountWalk[position[0]][position[1]-1]=1;
            mapCountWalk[position[0]][position[1]-2]=1;
            map[position[0]][position[1]-1]=0;
            map[position[0]][position[1]-2]=0;
        }

        for(int i=0;i<4;i++){
            if(map[mark[i][0]][mark[i][1]]<drop1BoxLEFT){
                map[mark[i][0]][mark[i][1]]=0;
            }

        }
    }
}

//=========================TEST==============
void printMap(){
    for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    printf("%d\t",map[i][j]);
                }
                printf("\n");
            }
            printf("\n");
}
void test(){
    if(direction==8){
        map[minX][minY]=98;
    }
    else if(direction==2){
        map[minX][minY]=92;
    }
    else if(direction==4){
        map[minX][minY]=94;
    }
    else if(direction==1){
        map[minX][minY]=91;
    }
}
void turnLeft(){
    printf("L*");
    if(direction == 8)direction = 1;
    else if(direction == 4)direction = 8;
    else if(direction == 2)direction = 4;
    else if(direction == 1)direction = 2;
}
void turnRight(){
    printf("R*");
    if(direction == 8)direction = 4;
    else if(direction == 4)direction = 2;
    else if(direction == 2)direction = 1;
    else if(direction == 1)direction = 8;
}
//====================================== Field code ======================
void printMapCountWalk(){
    printf("\n ======================== Map count walk\n");
    for(int i =0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(position[0] == i && position[1] == j) printf("X ");
            else printf("%d ",mapCountWalk[i][j]);
        }
        printf("\n");
    }
    printf("\tdirection = %d\n",direction);
}

int searchNext(){
    if(searchTarget[0] != 0 || searchTarget[1] != 8){
        if(searchTarget[0]%2 == 0){ //8 6 4 2 0 search left
            if(searchTarget[1] == 1){
                searchTarget[0]--;  // row -1 (up)
            }else{
                searchTarget[1]--;  // col -1 (left)
            }
        }else{                      //9 7 5 3 1 search right
            if(searchTarget[1] == 8){
                searchTarget[0]--;  // row -1 (up)
                if(searchTarget[0] == 0)return 0; //check case end point have box
            }else{
                searchTarget[1]++;  // col -1 (left)
            }
        }
        return 1;
    }else return 0;
}

int showMeDabox(){
    char a;
    do{
        do{
            printMapCountWalk();
            while(mapCountWalk[searchTarget[0]][searchTarget[1]] == 0){
                printf("WTF !!");
                if(!searchNext())return 0;
            }
            shortestPath(position[0],position[1],searchTarget[0],searchTarget[1]);
            a = runShortestRoute();
            if(a == 2)return 0;
        }while(a);
    }while(searchNext());
    printf("BYE !!");
    return 0;
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

int shortestPath(char targetRow,char targetCol,char startRow,char startCol){
    char i,j,row=startRow,col=startCol;
    int count=0;
    //printf("Start searching shortestPath \n From: %d,%d  -> %d,%d\n",startRow,startCol,targetRow,targetCol);

    typedef struct{
        char preRow,preCol,preDirection,isCheck;
    }Box;

    Box mapBox[10][10];

    //init mapNode
    for(i = 0;i<10;i++){
        for(j=0;j<10;j++){
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
            if((col-1 >= 0) && (mapCountWalk[row][col-1] == 1) &&(mapBox[row][col-1].isCheck == 0) && (mapBlockTurn[row][col-1] == 1)){
                //printf("left  ");
                            //set value to next Box
                mapBox[row][col-1].isCheck = 1;
                mapBox[row][col-1].preRow = row;
                mapBox[row][col-1].preCol = col;
                mapBox[row][col-1].preDirection = 1;
                if(row == targetRow && col-1 == targetCol){
                        //printf("Found !!!\n");
                    break;
                }
                appendHeap(row,col-1);
            }
            //top
            if((row-1 >= 0) &&(mapCountWalk[row-1][col] == 1) && (mapBox[row-1][col].isCheck == 0) && (mapBlockTurn[row-1][col] == 1)){

                //printf("Top  ");
                //set value to next Box
                mapBox[row-1][col].isCheck = 1;
                mapBox[row-1][col].preRow = row;
                mapBox[row-1][col].preCol = col;
                mapBox[row-1][col].preDirection = 8;
                if(row-1 == targetRow && col == targetCol){
                    //printf("Found !!!\n");
                    break;
                }
                appendHeap(row-1,col);
            }
            //right
            if((col+1 <= 9) &&(mapCountWalk[row][col+1] == 1 )&&( mapBox[row][col+1].isCheck == 0) && (mapBlockTurn[row][col+1] == 1)){

                //printf("right  ");
                            //set value to next Box
                mapBox[row][col+1].isCheck = 1;
                mapBox[row][col+1].preRow = row;
                mapBox[row][col+1].preCol = col;
                mapBox[row][col+1].preDirection = 4;
                if(row == targetRow && col+1 == targetCol){
                        //printf("Found !!!\n");
                    break;
                }
                appendHeap(row,col+1);
            }
            //bottom
            if((row+1 <= 9) &&(mapCountWalk[row+1][col] == 1) && (mapBox[row+1][col].isCheck == 0) && (mapBlockTurn[row+1][col] == 1)){

                //printf("bottom  ");
                            //set value to next Box
                mapBox[row+1][col].isCheck = 1;
                mapBox[row+1][col].preRow = row;
                mapBox[row+1][col].preCol = col;
                mapBox[row+1][col].preDirection = 2;
                if(row+1 == targetRow && col == targetCol){
                    //printf("Found !!!\n");
                    break;
                }
                appendHeap(row+1,col);
            }
            if(isHeapEmpty() == 0){
                popHeap();
                row = popRow;
                col = popCol;
            }

        }while(1);
        //generate route
        //for(int i= 0;i<routeSize;i++)route[i]=0;
        row = targetRow;
        col = targetCol;
        char index = 0,temp;

        do{
            route[index] = mapBox[row][col].preDirection;
            temp = row;
            row = mapBox[row][col].preRow;
            col = mapBox[temp][col].preCol;
        }while(route[index++] != 0);

		//set shortest path count
		countShortestPathBlock = strlen(route)+1;

        //clear heap
        clearHeap();

        //print route

        for(i=0;i<index-1;i++){
            //printf("%d ",route[i]);
        }


        index = 0;
    }


    //print searched box

/*
    for(i = 0;i<10;i++){
        for(j=0;j<10;j++){
            printf("%d ",mapBox[i][j].isCheck);
        }
        printf("\n");
    }
    printf("===================\n");

    //print mapBox direction
    for(i = 0;i<10;i++){
        for(j=0;j<10;j++){
            printf("%d ",mapBox[i][j].preDirection);
        }
        printf("\n");
    }*/

    //printMapCountWalk();

    //return route
}


int shortestPathV2(char targetRow,char targetCol,char startRow,char startCol){
    char i,j,row=startRow,col=startCol;
    int count=0;
    //printf("Start searching shortestPath \n From: %d,%d  -> %d,%d\n",startRow,startCol,targetRow,targetCol);

    typedef struct{
        char preRow,preCol,preDirection,isCheck;
    }Box;

    Box mapBox[10][10];

    //init mapNode
    for(i = 0;i<10;i++){
        for(j=0;j<10;j++){
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


            //bottom
            if((row+1 <= 9) &&(mapCountWalk[row+1][col] == 1) && (mapBox[row+1][col].isCheck == 0) && (mapBlockTurn[row+1][col] == 1)){
                printf("bottom  ");
                            //set value to next Box
                mapBox[row+1][col].isCheck = 1;
                mapBox[row+1][col].preRow = row;
                mapBox[row+1][col].preCol = col;
                mapBox[row+1][col].preDirection = 2;
                if(row+1 == targetRow && col == targetCol){
                        printf("Found !!!\n");
                    break;
                }
                appendHeap(row+1,col);
            }
            if(isHeapEmpty() == 0){
                popHeap();
                row = popRow;
                col = popCol;
            }
            //left
            if((col-1 >= 0) && (mapCountWalk[row][col-1] == 1) &&(mapBox[row][col-1].isCheck == 0) && (mapBlockTurn[row][col-1] == 1)){
                printf("left  ");
                            //set value to next Box
                mapBox[row][col-1].isCheck = 1;
                mapBox[row][col-1].preRow = row;
                mapBox[row][col-1].preCol = col;
                mapBox[row][col-1].preDirection = 1;
                if(row == targetRow && col-1 == targetCol){
                        printf("Found !!!\n");
                    break;
                }
                appendHeap(row,col-1);
            }
            //top
            if((row-1 >= 0) &&(mapCountWalk[row-1][col] == 1) && (mapBox[row-1][col].isCheck == 0) && (mapBlockTurn[row-1][col] == 1)){
                printf("Top  ");
                //set value to next Box
                mapBox[row-1][col].isCheck = 1;
                mapBox[row-1][col].preRow = row;
                mapBox[row-1][col].preCol = col;
                mapBox[row-1][col].preDirection = 8;
                if(row-1 == targetRow && col == targetCol){
                    printf("Found !!!\n");
                    break;
                }
                appendHeap(row-1,col);
            }
            //right
            if((col+1 <= 9) &&(mapCountWalk[row][col+1] == 1 )&&( mapBox[row][col+1].isCheck == 0) && (mapBlockTurn[row][col+1] == 1)){
                printf("right  ");
                            //set value to next Box
                mapBox[row][col+1].isCheck = 1;
                mapBox[row][col+1].preRow = row;
                mapBox[row][col+1].preCol = col;
                mapBox[row][col+1].preDirection = 4;
                if(row == targetRow && col+1 == targetCol){
                        printf("Found !!!\n");
                    break;
                }
                appendHeap(row,col+1);
            }
            printf("%d",count++);
            if(count > 100)return 0;
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

		//set shortest path count
		countShortestPathBlock = strlen(route)+1;

        //clear heap
        clearHeap();

        //print route

        for(i=0;i<index-1;i++){
            printf("%d ",route[i]);

        }


        index = 0;
    }
    return 1;


    //print searched box

/*
    for(i = 0;i<10;i++){
        for(j=0;j<10;j++){
            printf("%d ",mapBox[i][j].isCheck);
        }
        printf("\n");
    }
    printf("===================\n");*/
/*
    //print mapBox direction
    for(i = 0;i<10;i++){
        for(j=0;j<10;j++){
            printf("%d ",mapBox[i][j].preDirection);
        }
        printf("\n");
    }*/

    //printMapCountWalk();

    //return route
}


int moveForward(){
    int a;
    scanf("%d",&a);
    if(a == 1){
        if(direction == 8)position[0]--;
        else if(direction == 4)position[1]++;
        else if(direction == 2)position[0]++;
        else if(direction == 1)position[1]--;
    }
    return (char)a;
}

int runShortestRoute(){

    char i;
    printf("\nrunShortestRoute : ");
    for(i = 0;i<strlen(route);i++){
        switch(route[i]){
        case 8:                             //8 revert to 2
            if(direction == 1){
                printf("L+");
            }else if(direction == 8){
                printf("LL+");
            }else if(direction == 4){
                printf("R+");

            }
            //debug
            direction = 2;
            break;
        case 4:                             //4 revert to 1
            if(direction == 8){
                printf("L+");

            }else if(direction == 4){
                printf("LL+");
            }else if(direction == 2){
                printf("R+");
            }
            //debug
            direction = 1;
            break;
        case 2:                             //2 revert to 8
            if(direction == 4){
                printf("L+");
            }else if(direction == 2){
                printf("LL+");
            }else if(direction == 1){
                printf("R+");
            }

            //debug
            direction = 8;
            break;
        case 1:                             //1 revert to 4
            if(direction == 2){
                printf("L+");
            }else if(direction == 1){
                printf("LL+");
            }else if(direction == 8){
                printf("R+");
            }
            //debug
            direction = 4;
            break;
        default:;
        }
        printf("M+");

        // move with check front have a box ?
        char re = moveForward();
        if(re != 1){
            if(route[i] == 8 && mapCountWalk[position[0]+1][position[1]] == 1){
                mapCountWalk[position[0]+1][position[1]] = 0;
                map[position[0]+1][position[1]] = re;
                countBox++;
            }else if(route[i] == 4 && mapCountWalk[position[0]][position[1]-1] == 1){
                mapCountWalk[position[0]][position[1]-1] = 0;
                map[position[0]][position[1]-1] = re;
                countBox++;
            }else if(route[i] == 2 && mapCountWalk[position[0]-1][position[1]] == 1){
                mapCountWalk[position[0]-1][position[1]] = 0;
                map[position[0]-1][position[1]] = re;
                countBox++;
            }else if(route[i] == 1 &&  mapCountWalk[position[0]][position[1]+1] == 1){
                mapCountWalk[position[0]][position[1]+1] = 0;
                map[position[0]][position[1]+1] = re;
                countBox++;
            }
            //check search 8 box
            if(countBox == 8){
                for(int j = 0;j<routeSize;j++)route[j]=0;
                printf(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BREAK count = 8\n");
                countBox = 0;
                return 2;
            }
            return 1;
        }
        printMapCountWalk();
    }
    //clear route
    for(i = 0;i<routeSize;i++)route[i]=0;
    //finish
    return 0;
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

// search map avoid box
int checkTurnLeft(char row,char col,char d){
    if(d == 8){
        if(row>0 && mapCountWalk[row-1][col]==0)return 0;                   // TOP
        if(row>0 && col>0 && mapCountWalk[row-1][col-1]==0)return 0;        // LEFT TOP
        if(col>0 && mapCountWalk[row][col-1]==0)return 0;                   // LEFT
    }else if(d == 4){
        if(col<9 && mapCountWalk[row][col+1]==0)return 0;                   // RIGHT
        if(row>0 && col<9 && mapCountWalk[row-1][col+1]==0)return 0;        // RIGHT TOP
        if(row>0 && mapCountWalk[row-1][col]==0)return 0;                   // TOP
    }else if(d == 2){
        if(row<9 && mapCountWalk[row+1][col]==0)return 0;                   // BOTTOM
        if(row<9 && col<9 && mapCountWalk[row+1][col+1]==0)return 0;        // BOTTOM RIGHT
        if(col<9 && mapCountWalk[row][col+1]==0)return 0;                   // RIGHT
    }else if(d == 1){
        if(col>0 && mapCountWalk[row][col-1]==0)return 0;                   // LEFT
        if(row<9 && col>0 && mapCountWalk[row+1][col-1]==0)return 0;        // BOTTOM LEFT
        if(row<9 && mapCountWalk[row+1][col]==0)return 0;                   // BOTTOM
    }
    return 1;
}

int checkTurnRight(char row,char col,char d){
    if(d == 8){
        if(row>0 && mapCountWalk[row-1][col]==0)return 0;                   // TOP
        if(row>0 && col<9 && mapCountWalk[row-1][col+1]==0)return 0;        // RIGHT TOP
        if(col<9 && mapCountWalk[row][col+1]==0)return 0;                   // RIGHT
    }else if(d == 4){
        if(col<9 && mapCountWalk[row][col+1]==0)return 0;                   // RIGHT
        if(row<9 && col<9 && mapCountWalk[row+1][col+1]==0)return 0;        // BOTTOM RIGHT
        if(row<9 && mapCountWalk[row+1][col]==0)return 0;                   // BOTTOM
    }else if(d == 2){
        if(row<9 && mapCountWalk[row+1][col]==0)return 0;                   // BOTTOM
        if(row<9 && col>0 && mapCountWalk[row+1][col-1]==0)return 0;        // BOTTOM LEFT
        if(col>0 && mapCountWalk[row][col-1]==0)return 0;                   // LEFT
    }else if(d == 1){
        if(col>0 && mapCountWalk[row][col-1]==0)return 0;                   // LEFT
        if(row>0 && col>0 && mapCountWalk[row-1][col-1]==0)return 0;        // LEFT TOP
        if(row>0 && mapCountWalk[row-1][col]==0)return 0;                   // TOP
    }
    return 1;
}

int moveForwardTemp(){
        if(directionTemp == 8)positionTemp[0]--;
        else if(directionTemp == 4)positionTemp[1]++;
        else if(directionTemp == 2)positionTemp[0]++;
        else if(directionTemp == 1)positionTemp[1]--;
}

void addRouteCode(char c,int n){
    for(int i =0;i<n;i++){
        routeCode[routeCodeIndex] = c;
        printf("%c-",c);
        routeCodeIndex++;
    }
}

int checkShortestRoute(){
    positionTemp[0] = position[0];
    positionTemp[1] = position[1];
    directionTemp = direction;
    char i;
    printf("\nCheckShortestRoute from : %d,%d\n",positionTemp[0],positionTemp[1]);

    for(i = 0;i<strlen(route);i++){
        switch(route[i]){
        case 8:                             //8 revert to 2
            if(directionTemp == 1){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('L',1);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],1) && checkTurnRight(positionTemp[0],positionTemp[1],8) && checkTurnRight(positionTemp[0],positionTemp[1],4))addRouteCode('R',3);
                    else{
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 8){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],1))addRouteCode('L',2);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],4))addRouteCode('R',2);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 4){
                if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('R',1);
                else if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],8) && checkTurnLeft(positionTemp[0],positionTemp[1],1))addRouteCode('L',3);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }
            //debug
            directionTemp = 2;
            break;
        case 4:                             //4 revert to 1
            if(directionTemp == 8){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('L',1);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],4) && checkTurnRight(positionTemp[0],positionTemp[1],2))addRouteCode('R',3);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 4){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],8))addRouteCode('L',2);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],2))addRouteCode('R',2);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 2){
                if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('R',1);
                else if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],4) && checkTurnLeft(positionTemp[0],positionTemp[1],8))addRouteCode('L',3);
                else {
                    mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                    return 0;
                }
            }
            //debug
            directionTemp = 1;
            break;
        case 2:                             //2 revert to 8
            if(directionTemp == 4){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('L',1);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],2) && checkTurnRight(positionTemp[0],positionTemp[1],1))addRouteCode('R',3);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 2){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],4))addRouteCode('L',2);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],1))addRouteCode('R',2);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 1){
                if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('R',1);
                else if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],2) && checkTurnLeft(positionTemp[0],positionTemp[1],4))addRouteCode('L',3);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }

            //debug
            directionTemp = 8;
            break;
        case 1:                             //1 revert to 4
            if(directionTemp == 2){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('L',1);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],1) && checkTurnRight(positionTemp[0],positionTemp[1],8))addRouteCode('R',3);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 1){
                if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],2))addRouteCode('L',2);
                else if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp) && checkTurnRight(positionTemp[0],positionTemp[1],8))addRouteCode('R',2);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }else if(directionTemp == 8){
                if(checkTurnRight(positionTemp[0],positionTemp[1],directionTemp))addRouteCode('R',1);
                else if(checkTurnLeft(positionTemp[0],positionTemp[1],directionTemp) && checkTurnLeft(positionTemp[0],positionTemp[1],1) && checkTurnLeft(positionTemp[0],positionTemp[1],2))addRouteCode('L',3);
                    else {
                        mapBlockTurn[positionTemp[0]][positionTemp[1]] = 0;
                        return 0;
                    }
            }
            //debug
            directionTemp = 4;
            break;
        default:;
        }
        addRouteCode('M',1);
        //move forward
        moveForwardTemp();
    }

    //clear route
    //for(i = 0;i<routeSize;i++)route[i]=0;
    //finish
    return 1;
}

int decodeRoute(){
    for(int i =0;i<routeCodeIndex;i++){
        char code = routeCode[i];
        printf("%c\n",code);
        if(code == 'L'){
            turnLeft();
        }else if(code == 'R'){
            turnRight();
        }else if(code == 'M'){
            moveForward();
            printMapCountWalk();
        }
    }
}

int moveAvoidBox(char t_row,char t_col,char size){
    printf("moveAvoidBox -> Start %d,%d : Target %d,%d\n",position[0],position[1],t_row,t_col);
        char a,count=0;

        // find the way
        do{
            //printf("%d ",count++);
            //clear route
            for(int i = 0;i<strlen(route);i++)route[i]=0;
            for(int i = 0;i<routeCodeIndex;i++)routeCode[i]=0;
            routeCodeIndex=0;

            //check infinity loop
            if(!shortestPath(position[0],position[1],t_row,t_col)){
                return 0;
            }

            printf("route size :  %d ",strlen(route));

            if(size == 42 && t_row == 4 && t_col == 6)route[strlen(route)] = 8;
            else if(size == 42 && t_row == 7 && t_col == 6)route[strlen(route)] = 2;
            a= checkShortestRoute();
            printf("\n");
        }while(!a);

        //delete last M
        routeCode[--routeCodeIndex]=0;

        //print
        printf("\nshortest route Code : ");
        for(int i = 0;i<strlen(routeCode);i++){
            printf("%c",routeCode[i]);
        }
        printf("\nStarting DECODE ROUTE \n");
    //run code
    decodeRoute();

    // DROP !!!
    printf("!! DROP ITEM !!");

    //clear route
    for(int i = 0;i<strlen(route);i++)route[i]=0;
    for(int i = 0;i<routeCodeIndex;i++)routeCode[i]=0;
    routeCodeIndex=0;

    //clear map block turn
    for(int i =0;i<10;i++)
        for(int j=0;j<10;j++)
            mapBlockTurn[i][j]=1;
}

int dropYourBox(char t_row,char t_col,char size){

    if(!moveAvoidBox(t_row,t_col,size)){
        printf("BOOM!!!");
    }
    //drop item here

}
