

function main()
    

   --iterate over transformmed 
   local transformed = darwin.dtw.list_files_recursively("transformed",true)
   for i, file in ipairs(transformed) do
       local content = darwin.dtw.load_file(file)
       local new_content =replace_string(content, '#include "inner.h"', "")
   end


   if darwin.argv.one_of_args_exist("update_bear")  then
        update_bear()
   end
   if darwin.argv.one_of_args_exist("create_patch")  then
    create_patch()
   end
   if darwin.argv.one_of_args_exist("build")  then
    build()
   end
end 