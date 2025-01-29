

function main()
    
    local itens = darwin.dtw.list_files_recursively("transformed/",true)
    for i, item in ipairs(itens) do
        local content = darwin.dtw.load_file(item)
        local formmated = string.gsub(content, '#include "inner.h"', "")
        darwin.dtw.write_file(item, formmated)
    end



   -- if darwin.argv.one_of_args_exist("update_bear")  then
   --     update_bear()
   -- end

end 