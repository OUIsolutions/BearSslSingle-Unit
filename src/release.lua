
function generate_release()
   darwin.dtw.remove_any(RELEASE_FOLDER)
   local one_result =  darwin.camalgamator.generate_amalgamation(
        darwin.dtw.concat_path(OUTPUT_DIR,"one.c")
   )
   darwin.dtw.write_file(darwin.dtw.concat_path(RELEASE_FOLDER,ONE_NAME),one_result)


   local only_header_path = darwin.dtw.concat_path(OUTPUT_DIR,"src/fdeclare.inner.h")
   local only_headder = darwin.camalgamator.generate_amalgamation(only_header_path)
   darwin.dtw.write_file(darwin.dtw.concat_path(RELEASE_FOLDER,ONLY_HEADER_NAME),only_headder)

   local only_define_path = darwin.dtw.concat_path(OUTPUT_DIR,"imports/imports.fdefine.h")
   local only_define_content = darwin.camalgamator.generate_amalgamation_with_callback(
        only_define_path,
        function (path,import)
             if string.find(import,"fdeclare.h") then
                return "dont-include"
             end 
            return "include-once" 
        end
   )    
   local pre_include = "#define BR_ENABLE_INTRINSICS   1\n"
   pre_include = pre_include.."#include \"BearSSLSingleUnit.h\"\n"
   only_define_content = pre_include..only_define_content

  
   darwin.dtw.write_file(darwin.dtw.concat_path(RELEASE_FOLDER,ONLY_DEFINE_NAME),only_define_content)

   local zip_path = darwin.dtw.concat_path(RELEASE_FOLDER,ZIP_NAME)
   os.execute("zip -r "..zip_path.." "..OUTPUT_DIR.."/")
end 