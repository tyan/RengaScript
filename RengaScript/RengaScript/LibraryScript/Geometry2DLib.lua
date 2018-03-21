local Geometry2DLib = {}

local rectFuncHelp = "Rect() require 4 numbers or two 2D points"

function Rect(...)
	for key,value in pairs {...} do 
		local argtype = type(value)
		if(argtype == "number") then
			assert(select("#",...) == 4, rectFuncHelp)
			return RectByCoord(...)
		elseif(argtype == "userdata") then
			if (value.type == "Point2D") then
				assert(select("#",...) == 2, rectFuncHelp)
				return RectByPoint(...)
			end
		end
	end
	error(rectFuncHelp)
	return nil
end

return Geometry2DLib