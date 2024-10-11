---@param json_main_replacer table
---@param file DtwTreePart
function Aply_file_modification(json_main_replacer, file)
    local is_c_file = false
    if file.path.get_extension() == "c" then
        is_c_file = true
        local new_name = DEFINE_NAME .. file.path.get_name()
        file.path.set_name(new_name)
        file.hardware_modify()
    end

    if file.path.get_extension() == "h" then
        is_c_file = true
        file.get_value()
        local new_name = DECLARE_NAME .. file.path.get_name()
        file.path.set_name(new_name)
        file.hardware_modify()
    end

    if is_c_file then
        local content = file.get_value()
        local formmated = Aply_main_replace(main_replace_json, content)
        file.set_value(formmated)
    end
end
