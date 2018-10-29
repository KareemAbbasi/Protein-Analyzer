////
//// Created by owner on 26/10/2018.
////
//#include <stdio.h>
//#include <math.h>
//#include <string.h>
//#include <stdlib.h>
//
//char fileChars[200][50];
//
//int startsWithss(char *a, char *b){
//    if (strncmp(a,b, sizeof(b))== 0) return 1;
//    return 0;
//}
//
//int openFile(char fileName[], char fileLines[][10]){
//    int line = 0;
//    FILE *file;
//    file = fopen(fileName, "r");
//    if (file){
//        char currLine[80];
//        char emptyArray[80];
//        while(fgets(currLine, sizeof(currLine), file)){
//            if (startsWithss(currLine, "ATOM")){
//                strcpy(fileLines[line], currLine);
//                line ++;
//
//            }
//        }
//    }
//    return 0;
//
//}
//
//
//int main(){
////    char fileLines[10][10];
////    openFile("C:\\Users\\owner\\Desktop\\targil1\\HI", fileLines);
////    for (int i=0; i< sizeof(fileLines)/ sizeof(fileLines[0]); ++i){
////        printf("%s", fileLines[i]);
////    }
//    char hi[5], *stop;
//    float h;
//
//    for (int i=0; i<5; ++i){
//        hi[i] = (char)"2";
//    }
//    h = strtof(hi, &stop);
//    printf("%f", h);
//
//}
