#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int startsWith(char *a, char *b){
    if (strncmp(a,b, 4)== 0) return 1; //TODO change the 4
    return 0;
}



int readFile(char fileName[], char fileLines[][90]){
    int line = 0;
    FILE *file;
    file = fopen(fileName, "r");


    if (file){
        while(fgets(fileLines[line], 90, file)){ //TODO change the 80;
            line++;
            if (line >= 20000){ //TODO change the 20000;
                break;
            }
        }
    }
    fclose(file);
    return 0;
}


int findAtomCoordinates(char fileLines[][90], float atomsArray[20000][3]){
    int atomCount=0;
    for (int i = 0; i < 20000; ++i){ //TODO change the sizeof
        if (startsWith(fileLines[i], "ATOM")){

            char xCoordinate[8];
            char yCoordinate[8];
            char zCoordinate[8];

            char *end;

            memset(xCoordinate, '\0', sizeof(xCoordinate));
            memset(yCoordinate, '\0', sizeof(yCoordinate));
            memset(zCoordinate, '\0', sizeof(zCoordinate));

            strncpy(xCoordinate, fileLines[i]+31, 7);
            strncpy(yCoordinate, fileLines[i]+39, 7);
            strncpy(zCoordinate, fileLines[i]+47, 7);


            atomsArray[atomCount][0] = strtof(xCoordinate, &end);
            atomsArray[atomCount][1] = strtof(yCoordinate, &end);
            atomsArray[atomCount][2] = strtof(zCoordinate, &end);

            atomCount++;
        }
    }
    return atomCount;
}



float findAverageCoordinate(int coordinate, float atomsArray[20000][3], int atomCount) {
    float sum = 0;
    for (int i = 0; i < atomCount; ++i){
        sum += atomsArray[i][coordinate];
    }

    float ff =  sum/atomCount; //TODO change the name

    return ff;


}

int findCenterGravity(float centerGravity[3], float atomsArray[20000][3], int atomCount){
    for (int i = 0; i < 3; ++i){
        centerGravity[i] = findAverageCoordinate(i, atomsArray, atomCount);
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

float findRG(int atomCount, float centerGravity[3], float atomsArray[20000][3]){
    float sum = 0;

    for (int i=0; i<atomCount; ++i){
        sum += pow(distanceTwoPoint(centerGravity, atomsArray[i]),2);
    }

    return sqrtf(sum/atomCount);
}

float findDmax(int atomCount, float atomsArray[20000][3]){
    float Dmax = 0;
    for (int i = 0; i < atomCount; ++i){
        for (int j = i; j < atomCount; ++j){
            float dist = distanceTwoPoint(atomsArray[i], atomsArray[j]);
            if (dist > Dmax){
                Dmax = dist;
            }
        }
    }
    return Dmax;
}



int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {

            char *fileName;
            fileName = argv[i];
            char fileLines[20000][90] = {{"\0"}};
            float atomC[20000][3] = {{0}}; //TODO change name
            float centerGravity[3] = {0};
            float RG;
            float Dmax;
            readFile(fileName, fileLines);
            int atomsNum = findAtomCoordinates(fileLines, atomC);

            findCenterGravity(centerGravity, atomC, atomsNum);

            RG = findRG(atomsNum, centerGravity, atomC);
            Dmax = findDmax(atomsNum, atomC);

            printf("PDB file %s, %d atoms were read\n", fileName, atomsNum);
            printf("Cg = %f %f %f\n", centerGravity[0], centerGravity[1], centerGravity[2]);
            printf("Rg = %f\n", RG);
            printf("Dmax = %f\n", Dmax);
        }
    }
}