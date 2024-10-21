#include "../fonts.h"
#include <stdio.h>
#include <stdlib.h>
// these module only download the doTheWorld.h and install into dependencyss

void install_lib_with_curl(const char *lib,const char *name){
    char comand[1000]={0};
    sprintf(comand,"curl -L %s -o dependencies/%s",lib,name);
    system(comand);
}


int main(){
    system("rm -rf dependencies");
    system("mkdir dependencies");
    install_lib_with_curl(DO_THE_WORLD,"doTheWorld.h");
    install_lib_with_curl(CTEXT_ENGINE,"CTextEngine.h");
    system("gcc stage1/main.c -o stage.o");
    system("./stage.o");
    return 0;
}
