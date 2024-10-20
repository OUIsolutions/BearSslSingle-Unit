local function main()
    if not dtw.isdir("BearSSL") then
        print(ANSI_BLUE .. "cloning BearSSL")
        os.execute("git clone " .. PROVIDER_GIT)
    else
        print(ANSI_YELLOW, "Bear cached")
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
    print(ANSI_BLUE .. "applying silver chain modifications")
    silver_chain.generate_code(
        new_src,
        dtw.concat_path(single_unit_dir, "imports"),
        SILVER_CHAIN_NAME,
        { "bear", DECLARE_NAME, DEFINE_NAME }
    )
    local one_file_path = dtw.concat_path(single_unit_dir, ONE_FILE)
    dtw.copy_any_overwriting("one.c", one_file_path)
    Create_summary(modifiers)
    print(ANSI_BLUE .. "Creating Final Amalgamation")
    local one_amalgamation = Generate_amalgamation_recursive(one_file_path)
    local one_amalgamation_release_path = dtw.concat_path(RELEASE_FODER, ONE_AMALGAMATION_NAME)
    dtw.write_file(one_amalgamation_release_path, one_amalgamation)


    print(ANSI_BLUE .. "Creating declare amalgamation")
    local fdeclare_path = dtw.concat_path(single_unit_dir, "imports/imports.fdeclare.h")
    local declare_amalgamation = Generate_amalgamation_recursive(fdeclare_path)
    local release_declare_path = dtw.concat_path(RELEASE_FODER, DECLARE_AMALGAMATION_NAME)
    dtw.write_file(release_declare_path, declare_amalgamation)

    print(ANSI_BLUE .. "Creating define amalgamation")
    local fdefine_path = dtw.concat_path(single_unit_dir, "imports/imports.fdefine.h")
    local definition_amalgamation = Generate_amalgamation_recursive(fdefine_path, { 'fdeclare' })
    definition_amalgamation = definition_amalgamation .. "#define BR_ENABLE_INTRINSICS   1\n"
    definition_amalgamation = definition_amalgamation .. '#include "BearSSL.h"\n'
    local release_fdefine_path = dtw.concat_path(RELEASE_FODER, DEFINE_AMALGAMATION_NAME)
    dtw.write_file(release_fdefine_path, definition_amalgamation)
end
main()
