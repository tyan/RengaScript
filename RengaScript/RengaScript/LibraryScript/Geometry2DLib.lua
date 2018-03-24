local Geometry2DLib = {}

-----------------------------------------------------------------------
-- Rect function
-----------------------------------------------------------------------
local rectFuncHelp = "Rect(...) require 4 numbers or two 2D points."

function Rect(...)
	for key,value in pairs {...} do 
		local argtype = type(value)
		if(argtype == "number") then
			assert(select("#",...) == 4, rectFuncHelp)
			return RectByCoord(...)
		elseif(argtype == "userdata") then
			if (value.type == "Point") then
				assert(select("#",...) == 2, rectFuncHelp)
				return RectByPoint(...)
			end
		end
	end
	error("Unrecognized arguments of Rect(...) function. "..rectFuncHelp)
	return nil
end


-----------------------------------------------------------------------
-- LineSegment function
-----------------------------------------------------------------------
local lineSegmentFuncHelp = "LineSegment(...) require 4 numbers or two 2D points."

function LineSegment(...)
	for key,value in pairs {...} do 
		local argtype = type(value)
		if(argtype == "number") then
			assert(select("#",...) == 4, lineSegmentFuncHelp)
			return LineSegmentByCoord(...)
		elseif(argtype == "userdata") then
			if (value.type == "Point") then
				assert(select("#",...) == 2, lineSegmentFuncHelp)
				return LineSegmentByPoint(...)
			end
		end
	end
	error("Unrecognized arguments of LineSegment(...) function. "..lineSegmentFuncHelp)
	return nil
end

return Geometry2DLib