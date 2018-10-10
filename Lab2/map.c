# include<stdio.h>


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

char map[9][9]={
    9,8,8,8,8,8,8,8,12,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    1,0,0,0,0,0,0,0,4,
    3,2,2,2,2,2,2,2,6
};
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
};*/

char posRow = 8,posCol = 8,robotDirection = 8;

char getMapWall(char x,char y){
    return map[x][y];
}


char getWall(int s1,int s2,int s3,char x,char y,char direction){
    //read 3 Ultra sonic Sensor
    // s1 top | s2 right | s3 left
    int wallDistance = 20;
    char wall = 0;
    switch(direction){
    case 8://top                       || WALL ||
        if(s1 < wallDistance)wall+=8;   //top
        if(s2 < wallDistance)wall+=4;   //right
        if(s3 < wallDistance)wall+=1;   //left
        break;
    case 4://right
        if(s1 < wallDistance)wall+=4;   //left
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
        if(s2 < wallDistance)wall+=2;   //bottom
        if(s3 < wallDistance)wall+=8;   //top
    break;
    default:;
    }
    return (wall | getMapWall(x,y));
}

//x,y  0-8
void setMapWall(char x,char y,char wall){
    map[x][y] = wall;                   //set this box
    if((wall & 8) && (x-1 >= 0 )){      //add bottom wall to top box
        map[x-1][y] = map[x-1][y] | 2;
    }
    if((wall & 4) && (y+1 <= 8 )){      //add left wall to right box
        map[x][y+1] = map[x][y+1] | 1;
    }
    if((wall & 2) && (x+1 <= 8 )){      //add top wall to bottom box
        map[x+1][y] = map[x+1][y] | 8;
    }
    if((wall & 1) && (y-1 >= 0 )){      //add right wall to left box
        map[x][y-1] = map[x][y-1] | 4;
    }
}




void printMap(){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}

void printMapV2(){
    char mapWall[27][27];
    int i,j,x,z;

    //init mapWall
    for(i = 0;i<27;i++){
        for(j=0;j<27;j++){
            mapWall[i][j] = '.';
        }
    }

    /*
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if((map[i][j] & 8) > 0){mapWall[i*2+i][(j*2)+j] = '_';}
            if((map[i][j] & 4) > 0)mapWall[(i*2)+1+i][(j*2)+2+j] = '|';
            if((map[i][j] & 2) > 0){mapWall[(i*2)+2+i][(j*2)+j] = '_';}
            if((map[i][j] & 1) > 0)mapWall[(i*2)+1+j][j*2+i] = '|';
        }
    }*/

    /*
    i=0;
    j=8;
    if((map[i][j] & 8) > 0)mapWall[i*3][(j*3)+1] = '_';
    if((map[i][j] & 4) > 0)mapWall[(i*3)+1][(j*3)+2] = '|';
    if((map[i][j] & 2) > 0)mapWall[(i*3)+2][(j*3)+1] = '_';
    if((map[i][j] & 1) > 0)mapWall[(i*3)+1][j*3] = '|';*/


    for(i = 0;i<27;i++){
        for(j=0;j<27;j++){
            printf("%c",mapWall[i][j]);
        }
        printf("\n");
    }
}

void shortedPath(char targetRow,char targetCol,char startRow,char startCol){

}

void main(){
    /*
    setMapWall(6,6,getWall(50,10,10,6,6,8));
    setMapWall(5,6,getWall(10,10,50,5,6,8));
    setMapWall(5,5,getWall(50,10,10,5,5,1));
    setMapWall(5,4,getWall(10,50,10,5,4,1));
    setMapWall(4,4,getWall(50,10,10,4,4,8));
    printMap();*/

    //printMap();
    //printMapV2();



}

