#include <stdio.h>
#include <stdlib.h>
#include "../config/all.h"
#include "../dependencies/doTheWorld.h"
#include "../dependencies/UniversalGarbage.h"

DtwNamespace dtw;
UniversalGarbage *garbage;

void download_git_model(const char *url,const char *name){
    char command[1000]= {0};
    sprintf(command,"%s clone %s",GIT_COMMAND,url);
    system(command);
    char *element_src = dtw.concat_path(name,"src");
    UniversalGarbage_add_simple(garbage, element_src);

    char *final_path = dtw.concat_path("dependencies",element_src);
    UniversalGarbage_add_simple(garbage,final_path);

    dtw.copy_any(element_src,final_path,DTW_NOT_MERGE);
    dtw.remove_any(name);
}




int main(){
    dtw = newDtwNamespace();
    garbage = newUniversalGarbage();
    download_git_model(SILVER_CHAIN, "SilverChain");
    download_git_model(LUA_DO_THE_WORLD, "LuaDoTheWorld");
    UniversalGarbage_free(garbage);

}
