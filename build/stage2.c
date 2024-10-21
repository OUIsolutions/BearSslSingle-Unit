

#include "../dependencies/CTextEngine.h"
#include "../dependencies/doTheWorld.h"
#include "../dependencies/UniversalGarbage.h"
#include "../dependencies/SilverChain/src/imports/imports.func_definition.h"
#include "../config/all.h"
#include <string.h>

DtwNamespace dtw;
CTextStackModule stack;
UniversalGarbage *garbage;

void parse_code(CTextStack *final,unsigned  char *content,long size){
    for(int i = 0; i < size; i++){
        stack.format(final," %d,",(unsigned char )content[i]);
    }
}

bool its_stack_array_empty(CTextStack *s){
    if(s->size == 0){
        return false;
    }
    return true;
}
void create_lua_consts(){



    DtwTree * conf_tree = dtw.tree.newTree();
    UniversalGarbage_add(garbage,dtw.tree.free,conf_tree);

    CTextStack *lua_consts = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free, lua_consts);

    dtw.tree.add_tree_from_hardware(conf_tree,CONF_FOLDER,(DtwTreeProps){
        .hadware_data = DTW_INCLUDE,
        .path_atributes = DTW_INCLUDE
    });

    CTextArray *lines = NULL;
    UniversalGarbage_add(garbage, CTextArray_free, lines);

    CTextArray *separations =NULL;
    UniversalGarbage_add(garbage, CTextArray_free, separations);

    CTextArray *non_empty_separations = NULL;
    UniversalGarbage_add(garbage, CTextArray_free, non_empty_separations);


    for(int i = 0; i < conf_tree->size;i++){
        DtwTreePart *current_file = conf_tree->tree_parts[i];
        if(!current_file->content){
            continue;
        }

        lines = CTextArray_split((char*)current_file->content,"\n");
        UniversalGarbage_resset(garbage, lines);
        for(int i = 0; i < lines->size;i++){

            separations = CTextArray_split(lines->stacks[i]->rendered_text," ");
            UniversalGarbage_resset(garbage, separations);

            non_empty_separations = CTextArray_filter(separations,its_stack_array_empty);
            UniversalGarbage_resset(garbage, non_empty_separations);

            if(non_empty_separations->size != 3){
                continue;
            }
            char *first = non_empty_separations->stacks[0]->rendered_text;
            char *second = non_empty_separations->stacks[1]->rendered_text;
            char *third = non_empty_separations->stacks[2]->rendered_text;

            if(strcmp(first, "#define") !=0){
                continue;
            }

            stack.format(lua_consts,"%s = %s\n",second,third);
        }
    }
    char *consts_dir = dtw.concat_path(LUA_FOLDER,"constants.lua");
    UniversalGarbage_add_simple(garbage,consts_dir);
    dtw.write_string_file_content(consts_dir,lua_consts->rendered_text);

}


int  create_lua_code(){
    if(dtw.entity_type(LUA_FOLDER) != DTW_FOLDER_TYPE){
        printf("lua code its not a folder\n");
        return 1;
    }

    CTextStack * final = stack.newStack_string_format("unsigned char  %s[]= {",LUA_VAR_NAME);
    UniversalGarbage_add(garbage,stack.free,final);

    DtwTree * tree = dtw.tree.newTree();
    UniversalGarbage_add(garbage,dtw.tree.free,tree);


    dtw.tree.add_tree_from_hardware(tree,LUA_FOLDER,(DtwTreeProps){
        .hadware_data = DTW_INCLUDE,
        .path_atributes = DTW_INCLUDE
    });

    DtwTreePart *main_code = NULL;
    for(int i = 0; i < tree->size;i++){

        DtwTreePart *current_file = tree->tree_parts[i];

        DtwPath *current_path = current_file->path;

        char *full_name = dtw.path.get_full_name(current_path);
        //means its a folder
        if(full_name == NULL){
            continue;
        }

        char *extension = dtw.path.get_extension(current_path);

        if(extension){
            if(strcmp(extension,"lua") != 0){
                continue;
            }
        }


        if(current_file->content == NULL || current_file->is_binary){
            char *full_path = dtw.path.get_path(current_path);
            printf("impossible to load content of %s\n",full_path);
            return 1;
        }



        if(strcmp(full_name,"main.lua")==0){
            main_code = current_file;
            continue;
        }
        parse_code(final,current_file->content,current_file->content_size);
    }
    if(main_code == NULL){
        printf("main code not provided\n");
        return 1;
    }
    parse_code(final,main_code->content,main_code->content_size);

    stack.text(final,"0};");

    dtw.write_string_file_content(OUTPUT_LUA,final->rendered_text);

    return 0;
}

int main(){
    dtw = newDtwNamespace();
    stack = newCTextStackModule();
    garbage  = newUniversalGarbage();
    create_lua_consts();



    int error = create_lua_code();
    if(error){
        UniversalGarbage_free(garbage);
        return error;
    }

    DtwStringArray *tags = newDtwStringArray();
    UniversalGarbage_add(garbage, dtw.string_array.free, tags);

    dtw.string_array.append(tags,DEPENDENCIES_FLAG);
    dtw.string_array.append(tags,CONST_FLAGS);
    dtw.string_array.append(tags,TYPES_FLAG);
    dtw.string_array.append(tags,GLOBALS_FLAG);
    dtw.string_array.append(tags,FDECLARE_FLAG);
    dtw.string_array.append(tags,FDEFINE_FLAG);

    generate_code("src/c","src/c/imports","silverchain_stage2",tags,true,DEFAULT_MAIN_C_NAME,NULL);

    CTextStack *final_compilation_linux = stack.newStack_string_format("gcc src/c/main.c -o %s",FINAL_OUPTUT_LINUX);
    error = system(final_compilation_linux->rendered_text);
    stack.free(final_compilation_linux);
    printf("aa\n");
    UniversalGarbage_free(garbage);


    if(error){
        return error;
    }

    return 0;
}
