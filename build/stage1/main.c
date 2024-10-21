#include <stdio.h>
#include <stdlib.h>
#include "../../config/all.h"
#include "../../dependencies/doTheWorld.h"
#include "../../dependencies/UniversalGarbage.h"

DtwNamespace dtw;
UniversalGarbage *garbage;

void download_silver_chain(){
    char command[1000]= {0};
    sprintf(command,"%s clone %s",GIT_COMMAND,SILVER_CHAIN);
    system(command);
    char *silver_chain_path = dtw.concat_path("dependencies","SilverChain/src");
    UniversalGarbage_add_simple(garbage,silver_chain_path);
    dtw.copy_any('')
}

int main(){
    dtw = newDtwNamespace();
    garbage = newUniversalGarbage();
    download_silver_chain();
    UniversalGarbage_free(garbage);

}
