function starts_with(str, prefix)
    return str:sub(1, #prefix) == prefix
end
function replace_string(str, old, new)
    local new_str = {}
    local i = 1
    while i <= #str do
        if starts_with(str:sub(i), old) then
            new_str[#new_str + 1] = new
            i = i + #old
        else
            new_str[#new_str + 1] = str:sub(i, i)
            i = i + 1
        end
    end
    return table.concat(new_str)
end