
function generate_release()

   local one_result =  darwin.camalgamator.generate_amalgamation(
        darwin.dtw.concat_path(OUTPUT_DIR,"one.c")
   )
   darwin.dtw.write_file(darwin.dtw.concat_path(RELEASE_FOLDER,ONE_NAME),one_result)


   local only_header_path = darwin.dtw.concat_path(OUTPUT_DIR,"src/fdeclare.inner.h")
   local only_headder = darwin.camalgamator.generate_amalgamation(only_header_path)
   darwin.dtw.write_file(darwin.dtw.concat_path(RELEASE_FOLDER,ONLY_HEADER_NAME),only_headder)


end 