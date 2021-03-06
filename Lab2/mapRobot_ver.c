
#define wallDistance 20
#define HeapSize 30
#define routeSize 30
#define stackSize 50

/*
bit 0000
    8421
bit 8    is top
bit  4   is right
bit   2  is bottom
bit    1 is left
    8
   1 4
    2
*/

// default map
/*
char map[9][9]={
    9,8,8,9,10,12,8,8,12,
    1,0,0,1,12,3,12,0,4,
    1,0,0,5,1,10,4,0,4,
    1,0,0,5,5,15,1,12,4,
    1,0,9,6,3,10,6,5,4,
    1,0,3,10,10,10,12,3,12,
    1,0,0,0,0,0,5,15,5,
    1,0,0,0,0,0,5,15,5,
    3,2,2,2,2,2,3,10,6
};*/

/*
char map[9][9] = {
    9,10,10,10,10,8,8,14,13,
    7,9,10,8,10,4,1,12,7,
    11,2,14,1,10,4,3,2,4,
    9,10,14,5,15,5,13,9,4,
    1,10,14,1,10,4,3,6,5,
    5,13,9,4,15,5,11,12,5,
    1,4,5,1,10,2,14,5,5,
    5,5,5,1,10,10,10,6,5,
    7,3,6,3,10,10,10,10,6
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

char map[9][9]={
	  15,15,15,15,15,15,15,15,15,
	  15,15,15,15,15,15,15,15,15,
    15,9,10,10,8,10,10,12,15,
    15,5,15,15,5,15,15,5,15,
    15,3,10,8,2,10,10,4,15,
    15,15,15,5,15,15,15,3,12,
    15,15,15,3,12,15,13,15,5,
    15,15,15,15,5,15,5,15,5,
    15,15,15,11,2,10,2,10,6
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

typedef struct{
    char next,row,col;
}Node;

Node heap[HeapSize];

char direction=8,posRow = 8, posCol = 8,popRow=0,popCol=0,useHeap=0,createHeap=0,nextHeap=1,route[routeSize],stack[stackSize],topStack=0;

char getMapWall(char row,char col){
    return map[row][col];
}

char getWall(float s1,float s2,float s3,char direction){
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
        printf("heap Row: %d Col: %d Next: %d | \n",heap[i].row,heap[i].col,heap[i].next);
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
        printf("\n========= route count: %d ===========\n",strlen(route));
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

        printf("\n========= route count: %d ===========\n",strlen(route));
        for(i=0;i<index-1;i++){
            printf("%d ",route[i]);
        }
        printf("\n====================\n");

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
                printf("L");
                //turn90left();
            }else if(direction == 8){
                printf("LL");
                //turn90left();
                //turn90left();
            }else if(direction == 4){
                printf("R");
                //turn90right();
            }
            //debug
            direction = 2;

            break;
        case 4:                             //4 revert to 1
            if(direction == 8){
                    printf("L");
                //turn90left();
            }else if(direction == 4){
                printf("LL");
                //turn90left();
                //turn90left();
            }else if(direction == 2){
                printf("R");
                //turn90right();
            }
            //debug
            direction = 1;
            break;
        case 2:                             //2 revert to 8
            if(direction == 4){
                    printf("L");
                //turn90left();
            }else if(direction == 2){
                printf("LL");
                //turn90left();
                //turn90left();
            }else if(direction == 1){
                printf("R");
                //turn90right();
            }
            //debug
            direction = 8;
            break;
        case 1:                             //1 revert to 4
            if(direction == 2){
                    printf("L");
                //turn90left();
            }else if(direction == 1){
                printf("LL");
                //turn90left();
                //turn90left();
            }else if(direction == 8){
                printf("R");
                //turn90right();
            }
            //debug
            direction = 4;
            break;
        default:;
        }
        printf("M");
        //move_forward();
    }
    //clear route
    for(i = 0;i<strlen(route);i++)route[i]=0;
    //finish
}

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

void printStack(){
    int i =0;
    for(i=0;i<strlen(stack);i++){
        printf("%d ",stack[i]);
    }
    printf("\n");
}


void main(){
    /*
    setMapWall(6,6,getWall(50,10,10,8));
    setMapWall(5,6,getWall(10,10,50,8));
    setMapWall(5,5,getWall(50,10,10,1));
    setMapWall(5,4,getWall(10,50,10,1));
    setMapWall(4,4,getWall(50,10,10,8));*/
    //printf("%d",map[8][8] & 8);
/*
    shortestPath(8,8,7,7);
    runShortestRoute();
    shortestPath(7,7,4,4);
    runShortestRoute();
    shortestPath(4,4,8,8);
    runShortestRoute();
*/
    pushStack(8);
    pushStack(8);
    pushStack(8);
    pushStack(4);
    printStack();
    direction = 4;
    while(isStackEmpty()){
        route[0] = popStack();
        runShortestRoute();
    }

    //printf("______________\n");
    //printMap();
    //printMapV2();
    //shortestPath(4,4,8,8);
}
