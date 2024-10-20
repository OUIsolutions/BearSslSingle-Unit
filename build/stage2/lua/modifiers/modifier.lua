---@param part DtwTreePart
---@return Modifier
function NewModifier(part)
    local self         = {}
    self.tree_part     = part
    self.original_path = part.path.get_full_path()
    print(ANSI_BLUE .. "Creating Modifier for " .. self.original_path)
    self.tokens        = Collect_tokens(self.original_path)
    self.macros        = Collect_macros(self.original_path)

    self.create_sumary = function()
        local filtrage_tokens = {}
        for i = 1, #self.tokens do
            local current = self.tokens[i]
            if current.replace then
                filtrage_tokens[#filtrage_tokens + 1] = current
            end
        end
        return {
            original_path = self.original_path,
            modified_path = self.modified_path,
            tokens = filtrage_tokens
        }
    end


    self.has_replace                 = function()
        for i = 1, #self.tokens do
            local current = self.tokens[i]
            if current.replace then
                return true
            end
        end
        return false
    end
    self.is_defined                  = function(token)
        for i = 1, #self.tokens do
            local current = self.tokens[i]
            if current.value == token then
                return true
            end
        end
        return false
    end

    ---@param all Modifier[]
    ---@param token string
    ---@return boolean
    self.is_defined_by_others        = function(all, token)
        for i = 1, #all do
            local current = all[i]

            if current ~= self then
                if current.is_defined(token) then
                    return true
                end
            end
        end
        return false
    end

    ---@param all Modifier[]
    self.resolve_redefinitions       = function(all)
        for i = 1, #self.tokens do
            local current = self.tokens[i]
            if self.is_defined_by_others(all, current.value) then
                current.replace = "private_" .. self.tree_part.path.get_only_name() .. current.value
            end
        end
    end
    ---@param all Modifier[]
    ---@param json_main_replacer table
    self.generate_file_modifications = function(all, json_main_replacer)
        self.resolve_redefinitions(all)
        local single_unit_dir = dtw.concat_path(RELEASE_FODER, SINGLE_UNIT_FOLDER)
        local name = self.tree_part.path.get_name()
        local extension = self.tree_part.path.get_extension()
        if extension == "h" then
            self.tree_part.path.set_name(DECLARE_NAME .. "." .. name)
        end
        if extension == "c" then
            self.tree_part.path.set_name(DEFINE_NAME .. "." .. name)
        end
        self.tree_part.path.replace_dirs("BearSSL/src", dtw.concat_path(single_unit_dir, "src"))

        self.modified_path = self.tree_part.path.get_full_path()

        local content = self.tree_part.get_value()

        for key, value in pairs(json_main_replacer) do
            content = clib.replace(content, key, value)
        end
        if extension == "c" then
            local predef = ""
            for i = 1, #self.tokens do
                local current = self.tokens[i]
                if current.replace then
                    predef = predef .. "#ifndef " .. current.value .. "\n"
                    predef = predef .. '#define ' .. current.value .. ' ' .. current.replace .. '\n'
                    predef = predef .. "#endif\n"
                end
            end
            local undef = ''

            for i = 1, #self.tokens do
                local current = self.tokens[i]
                if current.replace then
                    undef = undef .. '#undef ' .. current.value .. '\n'
                end
            end
            content = predef .. content
            content = content .. undef

            for i = 1, #self.macros do
                content = content .. "#undef " .. self.macros[i] .. "\n"
            end
        end

        self.tree_part.set_value(content)

        self.tree_part.hardware_write()
    end

    return self
end
