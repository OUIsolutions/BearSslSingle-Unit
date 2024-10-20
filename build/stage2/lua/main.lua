local function main()
    if not dtw.isdir("BearSSL") then
        os.execute("git clone " .. PROVIDER_GIT)
    end
<<<<<<< HEAD

    local single_unit_point = dtw.concat_path(RELEASE_FOLDER, SINGLE_UNIT_FOLDER)
    dtw.remove_any(single_unit_point)

    dtw.copy_any_overwriting("BearSSL/inc", single_unit_point .. "/inc")


    local src = dtw.newTree_from_hardware("BearSSL/src")
    main_replace_json = json.load_from_file("main_replace.json")

    src.each(function(current)
        Aply_file_modification(main_replace_json, current)
    end)
    src.commit()

    dtw.copy_any_merging("BearModel", single_unit_point)
    silver_chain.generate_code(
        single_unit_point .. "/src",
        single_unit_point .. "/imports",
        SILVER_CHAIN_NAME,
        { "bear", DECLARE_NAME, DEFINE_NAME }
    )
    dtw.copy_any_merging("BearModel", single_unit_point)
=======
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
    dtw.copy_any_merging("BearSSLModel", single_unit_dir)
    Create_summary(modifiers)
>>>>>>> ctags
end
main()
