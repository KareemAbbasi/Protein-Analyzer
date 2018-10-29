#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


float centerGravity[3];


int startsWith(char *a, char *b){
    if (strncmp(a,b, sizeof(b))== 0) return 1;
    return 0;
}



int readFile(char fileName[], char fileLines[][80]){
    int line = 0;
    FILE *file;
    file = fopen(fileName, "r");


    if (file){
        while(fgets(fileLines[line], 80, file)){ //TODO change the 80
            line++;
        }
    }

    fclose(file);
}


int findAtomCoordinates(char fileLines[][80], float atomsArray[][3]){
    int atomCount=0;
    for (int i = 0; i < 20000; ++i){ //TODO change the sizeof
        if (startsWith(fileLines[i], "ATOM")){

            char xCoordinate[8];
            char yCoordinate[8];
            char zCoordinate[8];

            memset(xCoordinate, '\0', sizeof(xCoordinate));
            memset(yCoordinate, '\0', sizeof(yCoordinate));
            memset(zCoordinate, '\0', sizeof(zCoordinate));

            strncpy(xCoordinate, fileLines[i]+31, 7);
            strncpy(yCoordinate, fileLines[i]+39, 7);
            strncpy(zCoordinate, fileLines[i]+47, 7);

//            atomsArray[i][0] = strtof(xCoordinate, NULL);
//            atomsArray[i][1] = strtof(yCoordinate, NULL);
//            atomsArray[i][2] = strtof(zCoordinate, NULL);

            atomsArray[atomCount][0] = strtof(xCoordinate, NULL);
            atomsArray[atomCount][1] = strtof(yCoordinate, NULL);
            atomsArray[atomCount][2] = strtof(zCoordinate, NULL);




            atomCount++;
        }
    }
    return atomCount;
}



//float findAverageCoordinate(int coordinate) {
//    float sum = 0;
//    for (int i = 0; i < arraySize; ++i){
//        sum += atoms[i][coordinate];
//    }
//
//    float coordinateAvegare = sum/arraySize;
//
//    return coordinateAvegare;
//}

//int findCenterGravity(){
//    for (int i = 0; i < 3; ++i){
//        centerGravity[i] = findAverageCoordinate(i);
//    }
//    return 0;
//}

float distanceTwoPoint(float p1[3], float p2[3]){
    float sum = 0;
    for (int i = 0; i <3; ++i) {
        sum += pow((p1[i] - p2[i]),2);
    }

    float dist = sqrtf(sum);
    return dist;
}

//float findRG(){
//    float sum = 0;
//
//    for (int i=0; i<arraySize; ++i){
//        sum += pow(distanceTwoPoint(centerGravity, atoms[i]),2);
//    }
//
//    return sqrtf(sum/arraySize);
//}




int main() {
    char *fileName;
    fileName = "C:\\Users\\owner\\Desktop\\targil1\\2g4j.pdb";
    char fileLines[20000][80];
    float atomC[20000][3];
    readFile(fileName, fileLines);
    int atomsNum = findAtomCoordinates(fileLines, atomC);

//    for (int i=0; i<12; ++i){
//        printf("%f, %f, %f\n", atomC[i][0], atomC[i][1], atomC[i][2]);
//    }

    printf("There are %d atoms in %s", atomsNum, fileName);



}