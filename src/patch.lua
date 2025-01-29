
function create_patch()
    darwin.dtw.remove_any(PATCH_DIR)
    local itens = darwin.dtw.list_files_recursively("transformed/",false)
    for i, item in ipairs(itens) do
        local  old = darwin.dtw.concat_path("origin",item)
        local  new = darwin.dtw.concat_path("transformed",item)
        local  patch = darwin.dtw.concat_path(PATCH_DIR,item..".patch")
        darwin.dtw.write_file(patch,"") -- just to ensure the file exists        
        os.execute("diff  "..old.." "..new.." > "..patch)
    end
end 
function aply_patch()
    darwin.dtw.copy_any_overwriting("origin",OUTPUT_DIR)
    local itens = darwin.dtw.list_files_recursively(PATCH_DIR,false)
    local itens = darwin.dtw.list_files_recursively("transformed/",false)
    for i, item in ipairs(itens) do
        local  dest = darwin.dtw.concat_path(OUTPUT_DIR,item)
        local  patch = darwin.dtw.concat_path(PATCH_DIR,item..".patch")
        os.execute("patch -p0 "..dest.." < "..patch)        
    end
end 