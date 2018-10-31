#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_IN_LINE 90
#define MAX_LINE_NUM 20000
#define NUM_OF_COORDINATES 3



/**
 * Checks if the string a contains the string b.
 * @param a the string to check its beginning.
 * @param b the string to check if it is in a.
 * @return 1 if a starts with b, 0 otherwise.
 */
int startsWith(char *a, char *b)
{
    if (strncmp(a, b, 6) == 0)
    {
        return 1;
    }
    return 0;
}


/**
 * Read the file with the given name and stores it in the given array.
 * @param fileName the path to the file to be read.
 * @param fileLines the array that the file will be stored in.
 * @return 0.
 */
int readFile(char fileName[], char fileLines[][CHAR_IN_LINE])
{
    int line = 0;
    FILE *file;
    file = fopen(fileName, "r");


    if (file)
    {
        while(fgets(fileLines[line], CHAR_IN_LINE, file))
        {
            line++;
            if (line >= MAX_LINE_NUM)
            {
                break;
            }
        }
    }
    fclose(file);
    return 0;
}

/**
 * Find the coordinates of the atoms from a given array of file lines and stores them in an other given
 * array as float values.
 * @param fileLines the array that contains the file lines to be read.
 * @param atomsArray the array that the coordinated will be stored in.
 * @return 0.
 */
int findAtomCoordinates(char fileLines[][CHAR_IN_LINE], float atomsArray[MAX_LINE_NUM][NUM_OF_COORDINATES])
{
    int atomCount = 0;
    for (int i = 0; i < MAX_LINE_NUM; ++i)
    {
        if (startsWith(fileLines[i], "ATOM  "))
        {

            char xCoordinate[8];
            char yCoordinate[8];
            char zCoordinate[8];

            char *end;

            memset(xCoordinate, '\0', sizeof(xCoordinate));
            memset(yCoordinate, '\0', sizeof(yCoordinate));
            memset(zCoordinate, '\0', sizeof(zCoordinate));

            strncpy(xCoordinate, fileLines[i] + 31, 7);
            strncpy(yCoordinate, fileLines[i] + 39, 7);
            strncpy(zCoordinate, fileLines[i] + 47, 7);


            atomsArray[atomCount][0] = strtof(xCoordinate, &end);
            atomsArray[atomCount][1] = strtof(yCoordinate, &end);
            atomsArray[atomCount][2] = strtof(zCoordinate, &end);

            atomCount++;
        }
    }
    return atomCount;
}


/**
 * Find the average coordinate value of a number of coordinates given in an array.
 * @param coordinate the number of the coordinate (0 - X, 1 - Y, 2 - Z).
 * @param atomsArray the array that has the coordinates of the atoms.
 * @param atomCount the number of atoms in the array.
 * @return 0
 */
float findAverageCoordinate(int coordinate, float atomsArray[MAX_LINE_NUM][NUM_OF_COORDINATES], int atomCount)
{
    float sum = 0;
    for (int i = 0; i < atomCount; ++i)
    {
        sum += atomsArray[i][coordinate];
    }

    float coordinateAvg =  sum / atomCount;

    return coordinateAvg;


}


/**
 * Find the center of gravity by finding the average of each coordinate in the given coordinates array and saves them
 * in a given array.
 * @param centerGravity the array where the center of gravity will be saved.
 * @param atomsArray the array that contains the coordinates of the atoms.
 * @param atomCount the number of atoms in the array.
 * @return 0
 */
int findCenterGravity(float centerGravity[NUM_OF_COORDINATES], float atomsArray[MAX_LINE_NUM][NUM_OF_COORDINATES], int atomCount)
{
    for (int i = 0; i < 3; ++i)
    {
        centerGravity[i] = findAverageCoordinate(i, atomsArray, atomCount);
    }
    return 0;
}


/**
 * Find the distance between two given point.
 * @param p1 the first point.
 * @param p2 the second point.
 * @return the distance between two point.
 */
float distanceTwoPoint(float p1[NUM_OF_COORDINATES], float p2[NUM_OF_COORDINATES])
{
    float sum = 0;
    for (int i = 0; i < 3; ++i)
    {
        sum += pow((p1[i] - p2[i]), 2);
    }

    float dist = sqrtf(sum);
    return dist;
}


/**
 * Find the RG.
 * @param atomCount the number of atoms in the atoms array.
 * @param centerGravity the array that hold the coordinates of the center of gravity.
 * @param atomsArray the array that holds the coordinates of the atoms.
 * @return RG.
 */
float findRG(int atomCount, float centerGravity[NUM_OF_COORDINATES], float atomsArray[MAX_LINE_NUM][NUM_OF_COORDINATES])
{
    float sum = 0;

    for (int i = 0; i < atomCount; ++i)
    {
        sum += pow(distanceTwoPoint(centerGravity, atomsArray[i]), 2);
    }

    return sqrtf(sum / atomCount);
}


/**
 * Finds the max distance between two atoms in the atom array.
 * @param atomCount the number of atoms in the atom array.
 * @param atomsArray the array that holds the coordinates of the atoms.
 * @return the max distance.
 */
float findDmax(int atomCount, float atomsArray[MAX_LINE_NUM][NUM_OF_COORDINATES])
{
    float Dmax = 0;
    for (int i = 0; i < atomCount; ++i)
    {
        for (int j = i; j < atomCount; ++j)
        {
            float dist = distanceTwoPoint(atomsArray[i], atomsArray[j]);
            if (dist > Dmax)
            {
                Dmax = dist;
            }
        }
    }
    return Dmax;
}


/**
 * the main method that runs the program.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {

            char *fileName;
            fileName = argv[i];
            char fileLines[MAX_LINE_NUM][CHAR_IN_LINE] = {{"\0"}};
            float atomsCoordinates[MAX_LINE_NUM][NUM_OF_COORDINATES] = {{0}};
            float centerGravity[NUM_OF_COORDINATES] = {0};
            float RG;
            float Dmax;
            readFile(fileName, fileLines);
            int atomsNum = findAtomCoordinates(fileLines, atomsCoordinates);

            findCenterGravity(centerGravity, atomsCoordinates, atomsNum);

            RG = findRG(atomsNum, centerGravity, atomsCoordinates);
            Dmax = findDmax(atomsNum, atomsCoordinates);

            printf("PDB file %s, %d atoms were read\n", fileName, atomsNum);
            printf("Cg = %f %f %f\n", centerGravity[0], centerGravity[1], centerGravity[2]);
            printf("Rg = %f\n", RG);
            printf("Dmax = %f\n", Dmax);
        }
    }
}