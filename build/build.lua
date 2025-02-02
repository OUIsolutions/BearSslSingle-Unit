

function build()
    aply_patch()
    local itens = darwin.dtw.list_files_recursively(OUTPUT_DIR,true)
    for i, item in ipairs(itens) do
        local path = darwin.dtw.newPath(item)
        local extension = path.get_extension()
        if extension == "c" or extension == "cpp" then
            local name = path.get_name()
            local new_name = "fdefine."..name
            path.set_name(new_name)
            darwin.dtw.move_any_overwriting(item,path.get_full_path())
            
        end
    end
    local itens = darwin.dtw.list_files_recursively(OUTPUT_DIR,true)
    for i, item in ipairs(itens) do

        local new_name = item
        new_name = string.gsub(new_name,"fdefine","")
        new_name = string.gsub(new_name,"fdeclare","")
        new_name = string.gsub(new_name,OUTPUT_DIR,"")
        new_name = string.gsub(new_name,"/","_")
        new_name = string.gsub(new_name,"%.","_")
        new_name = string.gsub(new_name,"__","_")
        new_name = string.gsub(new_name,"__","_")
        print("saving sha for "..item.." as "..new_name)

        --(BEAR_SINGLE_UNITY_FILE)
        local content = darwin.dtw.load_file(item)
        local new_content = string.gsub(content,"BEAR_SINGLE_UNITY_FILE",new_name)
        darwin.dtw.write_file(item,new_content)
    end

    local inner_name = darwin.dtw.concat_path(OUTPUT_DIR,"src/inner.h")
    local new_inner_name = darwin.dtw.concat_path(OUTPUT_DIR,"src/fdeclare.inner.h")
    darwin.dtw.move_any_overwriting(inner_name,new_inner_name)
 
    darwin.silverchain.generate({
        src = OUTPUT_DIR,
        project_short_cut = PROJECT_NAME,
        tags = {"fdeclare", "fdefine" },
        implement_main=false
    })
    darwin.dtw.copy_any_overwriting("one.c",darwin.dtw.concat_path(OUTPUT_DIR,"one.c"))

    


end 