#include "../fonts.h"
#include <stdio.h>
#include <stdlib.h>
// these module only download the doTheWorld.h and install into dependencyss


int main(){
    system("rm -rf dependencies");
    system("mkdir dependencies");
    char comand[1000] ={0};
    sprintf(comand,"curl -L %s -o dependencies/doTheWorld.h",DO_THE_WORLD);
    system(comand);


    system("gcc stage1/main.c -o stage.o");
    system("./stage.o");
    return 0;
}
