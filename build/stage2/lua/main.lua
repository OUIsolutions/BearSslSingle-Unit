local function main()
    if not dtw.isdir("BearSSL") then
        os.execute("git clone " .. PROVIDER_GIT)
    end
    local main_replace = json.load_from_file("main_replace.json")
    local src = dtw.newTree_from_hardware("BearSSL/src")
    dtw.remove_any(RELEASE_FODER)
    local modifiers = Create_modifiers(src)
    Generate_modifications(modifiers, main_replace)
    src.commit()
    --release/BearSSLSingleUnit/src/
    --collect_tags()
    local single_unit_dir = dtw.concat_path(RELEASE_FODER, SINGLE_UNIT_FOLDER)
    dtw.copy_any_overwriting("BearSSL/inc", dtw.concat_path(single_unit_dir, "inc"))
    local new_src = dtw.concat_path(single_unit_dir, "src")
    silver_chain.generate_code(
        new_src,
        dtw.concat_path(single_unit_dir, "imports"),
        SILVER_CHAIN_NAME,
        { "bear", DECLARE_NAME, DEFINE_NAME }
    )
    local one_file_path = dtw.concat_path(single_unit_dir, ONE_FILE)
    dtw.copy_any_overwriting("one.c", one_file_path)
    Create_summary(modifiers)
    local final_amalgamation = Generate_amalgamation_recursive(one_file_path)
    local amalgamation_path = dtw.concat_path(RELEASE_FODER, AMALGAMATION_NAME)
    dtw.write_file(amalgamation_path, final_amalgamation)
end
main()
