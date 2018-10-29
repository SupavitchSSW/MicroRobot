#include <stdio.h>
//Jane
void mergeBox();

//field
#define wallDistance 18
#define routeSize 30
#define HeapSize 30
#define stackSize 50

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
int runShortestRoute();
void pushStack(char num);
char popStack(void);
char isStackEmpty(void);
int showMeDabox();
void printMapCountWalk();
int searchNext();
// ======= Shortest Path
//heap
typedef struct{
    signed char next,row,col;
}Node;

Node heap[HeapSize];
char popRow=0,popCol=0,useHeap=0,createHeap=0,nextHeap=1,route[routeSize],stack[stackSize],topStack=1,countShortestPathBlock=0,direction=8,countBox=0;
char position[2]={8,1},searchTarget[2]={8,9};

//Jane variable
int X=9,Y=9;
//*****************************************
//color 
//black=40 orange=41
int black=40,orange=41;
//grab1Box '^'=8 'v'=2 '>'= 4 '<' = 1
int grab1BoxUP=8,grab1BoxDOWN=2,grab1BoxRIGHT=4,grab1BoxLEFT=1;
//drop1Box '^'=18 'v'=12 '>'=14 '<' =11
int drop1BoxUP=18,drop1BoxDOWN=12,drop1BoxRIGHT=14,drop1BoxLEFT=11;
//grab2Box '^'=28 'v'=22 '>'=24 '<' =21
int grab2BoxUP=28,grab2BoxDOWN=22,grab2BoxRIGHT=24,grab2BoxLEFT=21;
//drop2Box '^'=38 'v'=32 '>'=34 '<' =31
int drop2BoxUP=38,drop2BoxDOWN=32,drop2BoxRIGHT=34,drop2BoxLEFT=31;
//***************************************** 
char map[10][10]={
  //0  1  2  3  4  5  6  7  8  9
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,41,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,40,0 ,0 ,0 ,0 ,
    0 ,40,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,40,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,41,41,0 ,40,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,41,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
    0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
};

//serch canWalk=1 cant=0
char mapCountWalk[10][10]={
  //0 1 2 3 4 5 6 7 8 9
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,0,1,1,1,
    1,1,1,1,1,0,1,1,1,1,
    1,0,1,1,1,1,1,1,1,1,
    1,1,1,1,0,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,1,0,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1
};

void main(){
    // showMeDabox();
    printf('eiei');
    mergeBox();
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf('%d ',map[i][j]);
        }
    }
}
//====================================== Jane Code =======================
void mergeBox(){
    for(int i=1;i<X;i++){
        for(int j=1;j<Y;j++){
            printf('eiei');
            if(map[i][j]==orange){
                //one Box check around Box
                if(map[i-1][j]!=orange && map[i+1][j]!=orange && map[i][j-1]!=orange && map[i][j+1]!=orange){
                    //Top of Box
                    if(map[i][j-1]!=orange && map[i][j-1]!=black){
                        map[i][j-1]=grab1BoxDOWN;
                    }
                    //Buttom of Box
                    if(map[i][j+1]!=orange && map[i][j+1]!=black){
                        map[i][j+1]=grab1BoxUP;
                    }
                    //Left of Box
                    if(map[i-1][j]!=orange && map[i-1][j]!=black){
                        map[i-1][j]=grab1BoxRIGHT;
                    }
                    //Right of Box
                    if(map[i+1][j]!=orange && map[i+1][j]!=black){
                        map[i+1][j]=grab1BoxLEFT;
                    }
                }//End if check around 1 Box

                //two Box check Box
                else{
                    //Box in Column
                    if((map[i][j-1]==orange)||(map[i][j+1]==orange)){
                        //UP
                        if(map[i][j-1]==orange){
                            if(map[i][j-2]!=black){
                                map[i][j-2]=grab2BoxDOWN;
                            }
                            if(map[i][j+1]!=black){
                                map[i][j+1]=grab2BoxUP;
                            }
                        }
                        //DOWN
                        else if(map[i][j+1]==orange){
                            if(map[i][j+2]!=black){
                                map[i][j+2]=grab2BoxUP;
                            }
                            if(map[i][j-1]!=black){
                                map[i][j-1]=grab2BoxDOWN;
                            }
                        }
                        map[i][j-1]=grab1BoxDOWN;
                    }//End if Box in Column
                    
                    //Box in Row
                    if((map[i-1][j]==orange)||(map[i+1][j]==orange)){
                        //LEFT
                        if(map[i-1][j]==orange){
                            if(map[i-2][j]!=black){
                                map[i-2][j]=grab2BoxRIGHT;
                            }
                            if(map[i+1][j]!=black){
                                map[i+1][j]=grab2BoxLEFT;
                            }
                        }
                        //RIGHT
                        if(map[i+1][j]==orange){
                            if(map[i-1][j]!=black){
                                map[i-1][j]=grab2BoxRIGHT;
                            }
                            if(map[i+2][j]!=black){
                                map[i+2][j]=grab2BoxLEFT;
                            }
                        }
                    }//End if Box in Row
                }//End if check 2 Box

            }//End if check IS Box

        }//End for J
    }//End for I    

}
void findNearBox(){
    
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
                if(!searchNext())return 0;
            }
            shortestPath(position[0],position[1],searchTarget[0],searchTarget[1]);
            a = runShortestRoute();
            if(a == 2)return 0;
        }while(a);
    }while(searchNext());
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

void shortestPath(char targetRow,char targetCol,char startRow,char startCol){
    char i,j,row=startRow,col=startCol;
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
            if((col-1 >= 0) && (mapCountWalk[row][col-1] == 1) &&(mapBox[row][col-1].isCheck == 0)){
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
            if((row-1 >= 0) &&(mapCountWalk[row-1][col] == 1) && (mapBox[row-1][col].isCheck == 0)){
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
            if((col+1 <= 9) &&(mapCountWalk[row][col+1] == 1 )&&( mapBox[row][col+1].isCheck == 0)){
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
            if((row+1 <= 9) &&(mapCountWalk[row+1][col] == 1) && (mapBox[row+1][col].isCheck == 0)){
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

    for(i = 0;i<strlen(route);i++){
        switch(route[i]){
        case 8:                             //8 revert to 2
            if(direction == 1){
                printf("L");
            }else if(direction == 8){
                printf("LL");
            }else if(direction == 4){
                printf("R");

            }
            //debug
            direction = 2;
            break;
        case 4:                             //4 revert to 1
            if(direction == 8){
                printf("L");

            }else if(direction == 4){
                printf("LL");
            }else if(direction == 2){
                printf("R");
            }
            //debug
            direction = 1;
            break;
        case 2:                             //2 revert to 8
            if(direction == 4){
                printf("L");
            }else if(direction == 2){
                printf("LL");
            }else if(direction == 1){
                printf("R");
            }

            //debug
            direction = 8;
            break;
        case 1:                             //1 revert to 4
            if(direction == 2){
                printf("L");
            }else if(direction == 1){
                printf("LL");
            }else if(direction == 8){
                printf("R");
            }
            //debug
            direction = 4;
            break;
        default:;
        }
        printf("M");
        // move with check front have a box ?
        if(countBox == 8){
            for(int j = 0;j<routeSize;j++)route[j]=0;
            printf(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BREAK ");
            return 2;
        }
        if(moveForward() == 0){
            if(route[i] == 8 && mapCountWalk[position[0]+1][position[1]] == 1){
                mapCountWalk[position[0]+1][position[1]] = 0;
                countBox++;
            }else if(route[i] == 4 && mapCountWalk[position[0]+1][position[1]] == 1){
                mapCountWalk[position[0]][position[1]-1] = 0;
                countBox++;
            }else if(route[i] == 2 && mapCountWalk[position[0]-1][position[1]] == 1){
                mapCountWalk[position[0]-1][position[1]] = 0;
                countBox++;
            }else if(route[i] == 1 &&  mapCountWalk[position[0]][position[1]+1] == 1){
                mapCountWalk[position[0]][position[1]+1] = 0;
                countBox++;
            }
            return 1;
        }
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







/*
void popStackAndRun(){
		delay(500);
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
    				pushStack(8);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 4){																		//front wall is 4
    			if(mapCountWalk[position[0]][position[1]+1] == 0){
    				move_forward();
    				pushStack(4);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 2){																		//front wall is 2
    			if(mapCountWalk[position[0]+1][position[1]] == 0){
    				move_forward();
    				pushStack(2);
    				canPop = 0;
    				continue;
    			}
    		}
    		else if(direction == 1){																		//front wall is 1
    			if(mapCountWalk[position[0]][position[1]-1] == 0){
    				move_forward();
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
   					pushStack(8);
   					canPop = 0;
   					continue;
    			}
    		}
	    }

	    if(canPop)popStackAndRun();

    }while(!isStackEmpty());
}

*/
