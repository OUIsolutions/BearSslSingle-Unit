local name = "/aaa/bbb/ccc/ddd/eee/fff/ggg//hhh/iii/jjj.tx"
local sanitized = string.gsub(name, "/","_")
sanitized = string.gsub(sanitized,"__","_")
sanitized = string.gsub(sanitized,"%.","_")
print(sanitized)