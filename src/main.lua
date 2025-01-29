

function main()
    

  

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