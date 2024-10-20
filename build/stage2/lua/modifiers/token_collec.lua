---@param path string
---@return Token[]
function Collect_tokens(path)
    os.execute("ctags   --kinds-c=f" .. path)
    local content = dtw.load_file("tags")
    lines = clib.split(content, "\n")
    all_elements = {}
    for i = 1, #lines do
        local current = lines[i]
        if clib.get_char(current, 1) ~= "!" then
            local token = {}
            local separations = clib.split(current, "\t")
            token.value = separations[1]
            --local type =
            if token.value ~= "" then
                all_elements[#all_elements + 1] = token
            end
        end
    end
    return all_elements
end
