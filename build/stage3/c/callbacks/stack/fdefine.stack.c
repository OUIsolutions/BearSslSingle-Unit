
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end

LuaCEmbedResponse * LuaStack_delete_stack(LuaCEmbedTable *self,LuaCEmbed *args){
    CTextStack *s = (CTextStack*)lua.tables.get_long_prop(self,"stack");
    stack.free(s);
    return NULL;
}

LuaCEmbedResponse * LuaStack_append_val(LuaCEmbedTable *self,LuaCEmbed *args){
    char *value = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *erro_msg = lua.get_error_message(args);
        return lua.response.send_error(erro_msg);
    }
    CTextStack *s = (CTextStack*)lua.tables.get_long_prop(self,"stack");
    stack.format(s,"%s",value);
    return NULL;
}

LuaCEmbedResponse * LuaStack_get_str(LuaCEmbedTable *self,LuaCEmbed *args){
    CTextStack *s = (CTextStack*)lua.tables.get_long_prop(self,"stack");
    return lua.response.send_str(s->rendered_text);
}

LuaCEmbedResponse * create_newStack(LuaCEmbedTable *tr,LuaCEmbed *args){
    CTextStack *s  =stack.newStack_string_empty();
    LuaCEmbedTable *self = lua.tables.new_anonymous_table(args);
    lua.tables.set_long_prop(self,"stack",(long)s);
    lua.tables.set_method(self,"append",LuaStack_append_val);
    lua.tables.set_method(self,"__gc",LuaStack_delete_stack);
    lua.tables.set_method(self,"get_str",LuaStack_get_str);
    return lua.response.send_table(self);
}
