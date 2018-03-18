local Geometry2DLib = {}

function Rect(...)
	for key,value in pairs {...} do 
		local argtype = type(value)
		if(argtype == "number") then
			return RectByCoord(...)
		end
	end
	return nil
end

return Geometry2DLib