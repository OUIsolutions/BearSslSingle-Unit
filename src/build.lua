

function build()
    aply_patch()
    local itens = darwin.dtw.list_files_recursively(OUTPUT_DIR,true)
    for i, item in ipairs(itens) do
        local path = darwin.dtw.newPath(item)
        local extension = path.get_extension()
        if extension == "c" or extension == "cpp" then
            local name = path.get_name()
            local new_name = "fdefine"..name
            path.set_name(new_name)
            darwin.dtw.move_any_overwriting(item,path)
            
        end
    end
end 