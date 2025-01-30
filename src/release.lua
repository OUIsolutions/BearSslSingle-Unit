
function generate_release()

   local one_result =  darwin.camalgamator.generate_amalgamation(
        darwin.dtw.concat_path(OUTPUT_DIR,"one.c")
   )
   darwin.dtw.write_file(darwin.dtw.concat_path(RELEASE_FOLDER,ONE_NAME),one_result)
end 