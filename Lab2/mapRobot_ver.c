
#define wallDistance 20
#define HeapSize 30


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
    9,8,8,8,8,8,8,8,12,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,2,4,
    1,0,0,0,0,0,4,15,5,
    3,2,2,2,2,2,2,10,6
};*/


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


typedef struct{
    char next,row,col;
}Node,NNN;

Node heap[HeapSize];

char posRow = 8, posCol = 8,robotDirection = 8,useHeap=0,createHeap=0,nextHeap=1;

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
        map[row-1][col] = map[row-1][col] | 2;
    }
    if((wall & 4) && (col+1 <= 8 )){      //add left wall to right box
        map[row][col+1] = map[row][col+1] | 1;
    }
    if((wall & 2) && (row+1 <= 8 )){      //add top wall to bottom box
        map[row+1][col] = map[row+1][col] | 8;
    }
    if((wall & 1) && (col-1 >= 0 )){      //add right wall to left box
        map[row][col-1] = map[row][col-1] | 4;
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

struct Node popHeap(){
    Node n = heap[useHeap];
    heap[useHeap].next = -1;                   // already use
    useHeap += 1;
    if(useHeap == HeapSize)useHeap = 0;
    return n;
}


void shortedPath(char targetRow,char targetCol,char startRow,char startCol){
    char i,j,row=startRow,col=startCol,route[50];
    //printf("Start searching shorted path \n From: %d,%d  -> %d,%d\n",startRow,startCol,targetRow,targetCol);

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

    do{
      //  printf("search Row: %d Col: %d Wall: %d | ",row,col,map[row][col]);
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

        Node n = popHeap();
        row = n.row;
        col = n.col;

   //     printf("\n");
    }while(1);

    //print searched box

    /*
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

    //print route
    /*
    printf("\n========= route count: %d ===========\n",strlen(route));
    for(i=0;i<index-1;i++){
        printf("%d ",route[i]);
    }
    printf("\n====================\n");
    */

    //return route
}

task main(){
    /*
    setMapWall(6,6,getWall(50,10,10,8));
    setMapWall(5,6,getWall(10,10,50,8));
    setMapWall(5,5,getWall(50,10,10,1));
    setMapWall(5,4,getWall(10,50,10,1));
    setMapWall(4,4,getWall(50,10,10,8));*/
    //printf("%d",map[8][8] & 8);
    shortedPath(4,4,8,8);
    //printf("______________\n");
    //printMap();
    //printMapV2();
    //shortedPath(4,4,8,8);
}
