#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

float atoms[20000][3];
float arraySize = sizeof(atoms)/ sizeof(atoms[0]);

float centerGravity[3];


int startsWith(char *a, char *b){
    if (strncmp(a,b, sizeof(b))== 0) return 1;
    return 0;
}



int readFile(char fileName[], char *fileLines[]){
    int line = 0;
    FILE *file;
    file = fopen(fileName, "r");

    if (file){
        while(fgets(fileLines[line], sizeof(fileLines), file)){
            line++;
        }
    }
    return 0;
}


int findAtomCoordinates(char fileLines[][80], char atoms[][3]){

    int atomCount = 0;
    for (int i = 0; i < sizeof(fileLines)/ sizeof(fileLines[0]); ++i){
        if (startsWith(fileLines[i], "ATOM")){

            atomCount ++;
            char xCoordinate[7];
            char yCoordinate[7];
            char zCoordinate[7];

            for (int j = 31; j< 39; ++j){
                xCoordinate[j%31] = fileLines[i][j];
            }

            for (int j = 39; j<47; ++j){
                yCoordinate[j%39] = fileLines[i][j];
            }

            for (int j = 47; j < 55; ++j){
                zCoordinate[j%47] = fileLines[i][j];
            }

            atoms[atomCount][0] = (float)xCoordinate;
        }
    }
}



float findAverageCoordinate(int coordinate) {
    float sum = 0;
    for (int i = 0; i < arraySize; ++i){
        sum += atoms[i][coordinate];
    }

    float coordinateAvegare = sum/arraySize;

    return coordinateAvegare;
}

int findCenterGravity(){
    for (int i = 0; i < 3; ++i){
        centerGravity[i] = findAverageCoordinate(i);
    }
    return 0;
}

float distanceTwoPoint(float p1[3], float p2[3]){
    float sum = 0;
    for (int i = 0; i <3; ++i) {
        sum += pow((p1[i] - p2[i]),2);
    }

    float dist = sqrtf(sum);
    return dist;
}

float findRG(){
    float sum = 0;

    for (int i=0; i<arraySize; ++i){
        sum += pow(distanceTwoPoint(centerGravity, atoms[i]),2);
    }

    return sqrtf(sum/arraySize);
}




//int main() {
//    printf("%d", sizeof(atoms)/ sizeof(atoms[0]));
//}