
function create_patch()
    darwin.dtw.remove_any("patch/")
    local itens = darwin.dtw.list_files_recursively("transformed/",false)
    for i, item in ipairs(itens) do
        local  old = darwin.dtw.concat_path("origin",item)
        local  new = darwin.dtw.concat_path("transformed",item)
        local  patch = darwin.dtw.concat_path("patch",item)
        dtw.write_file(patch,"") -- just to ensure the file exists        
        os.execute("diff  "..old.." "..new.." > "..patch)
    end
end 