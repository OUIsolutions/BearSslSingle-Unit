

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
    local inner_name = darwin.dtw.concat_path(OUTPUT_DIR,"src/inner.h")
    local new_inner_name = darwin.dtw.concat_path(OUTPUT_DIR,"src/fdeclare.inner.h")
    dtw.move_any_overwriting(inner_name,new_inner_name)
 
    darwin.silverchain.generate({
        src = OUTPUT_DIR,
        project_short_cut = PROJECT_NAME,
        tags = {"fdeclare", "fdefine" },
        implement_main=false
    })
end 