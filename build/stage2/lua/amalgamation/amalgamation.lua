---@param start_point string
---@param stack Stack
---@param already_included_list  StringArray | nil
---@return string
function Generate_amalgamation_recursive_with_stack(stack, start_point, already_included_list)
    local start_point_sha = dtw.generate_sha_from_file(start_point)
    if already_included_list.is_included(start_point_sha) then
        print(ANSI_YELLOW .. "file" .. start_point .. "already included")
        return ""
    end

    already_included_list.append(start_point_sha)


    local content = dtw.load_file(start_point)

    local size = clib.get_str_size(content)
    local inside_string = false
    local waiting_include = false
    local string_buffer = ""
    for i = 1, size do
        local is_start_string = Verify_if_is_start_string_char(content, i, inside_string)
        if is_start_string then
            inside_string = true
        end

        local is_end_string = Verify_if_is_end_string_char(is_start_string, content, i, inside_string)

        if Include_char_to_string_buffer(is_start_string, is_end_string, inside_string) then
            string_buffer = string_buffer .. clib.get_char(content, i)
        end

        if Include_string_buffer_to_final(waiting_include, is_end_string) then
            stack.append('"' .. string_buffer .. '"')
        end

        if Is_include_point(content, i, inside_string) then
            waiting_include = true
        end

        if Anulate_inclusion(waiting_include, content, i) then
            stack.append("#include ")
            waiting_include = false
        end

        if Include_char_to_final(waiting_include, inside_string) then
            stack.append(clib.get_char(content, i))
        end



        if Make_recursive_call(waiting_include, is_end_string) then
            local dir = dtw.newPath(start_point).get_dir()
            local full_path = dtw.concat_path(dir, string_buffer)

            Generate_amalgamation_recursive_with_stack(stack, full_path, already_included_list)
            stack.append("\n")
            waiting_include = false
        end

        if is_end_string then
            inside_string = false
            string_buffer = ""
        end
    end

    print(ANSI_GREEN .. "amalgamated: " .. start_point)
end

---@param file string
---@return string
function Generate_amalgamation_recursive(file)
    local stack = clib.newStack()
    local already_included_list = Created_already_included();
    Generate_amalgamation_recursive_with_stack(stack, file, already_included_list)
    return stack.get_str()
end
