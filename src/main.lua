

function main()
    

   local transformmed = darwin.dtw.list_files_recursively("transformed",true)
   for i, v in ipairs(transformmed) do
       local file = transformmed[i]
       local content= darwin.dtw.load_file(file)
       var = 'api_order'
       local replaced = string.gsub(content, var, "(BEAR_SINGLE_UNITY_FILE)"..var)
       darwin.dtw.write_file(file, replaced)
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