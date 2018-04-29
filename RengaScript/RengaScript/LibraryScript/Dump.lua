-----------------------------------------------------------------------
-- Dump function
-----------------------------------------------------------------------
function Dump(arg)
	local argtype = type (arg)
	if(argtype == "userdata") then
		funcName = "Dump" .. arg.type
		if _G[funcName] == nil then
			error(funcName.." function not defined.")
			return
		end
		_G[funcName](arg)
		return
	end
	
	error("Unrecognized arguments of Dump(...) function.")
	return
end