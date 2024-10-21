---@param modifiers Modifier[]
function Create_summary(modifiers)
    all = {}
    for i = 1, #modifiers do
        local current = modifiers[i]
        if current.has_replace() then
            all[#all + 1] = current.create_sumary()
        end
    end

    json.dumps_to_file(all, dtw.concat_path(RELEASE_FODER, "sumary_src.json"))
end

---@param modifiers Modifier[]
---@param main_replace table
function Generate_modifications(modifiers, main_replace)
    for i = 1, #modifiers do
        local current = modifiers[i]
        print(ANSI_BLUE .. "generating Modifier for" .. current.tree_part.path.get_full_path())
        current.generate_file_modifications(modifiers, main_replace)
    end
end

---@param src DtwTree
---@return Modifier[]
function Create_modifiers(src)
    return src.map(function(item)
        local extension = item.path.get_extension()
        if extension == "c" or extension == "h" then
            return NewModifier(item)
        end
    end)
end
