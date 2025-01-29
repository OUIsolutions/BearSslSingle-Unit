
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