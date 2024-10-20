---@param path string
---@return Token[]
function Collect_macros(path)
    os.execute("ctags --kinds-c=d " .. path)
    local content = dtw.load_file("tags")
    local lines = clib.split(content, "\n")
    local all_macros = {}
    for i = 1, #lines do
        local current = lines[i]
        if clib.get_char(current, 1) ~= "!" then
            local separations = clib.split(current, "\t")
            local macro = separations[1]
            --local type =
            if macro ~= "" then
                all_macros[#all_macros + 1] = macro
            end
        end
    end
    return all_macros
end
