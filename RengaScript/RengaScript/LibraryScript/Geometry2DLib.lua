local Geometry2DLib = {}

-----------------------------------------------------------------------
-- Rect function
-----------------------------------------------------------------------
local rectFuncHelp = "Rect(...) requires 4 numbers or two points."

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
local lineSegmentFuncHelp = "LineSegment(...) requires 4 numbers or two points."

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

-----------------------------------------------------------------------
-- Contour function
-----------------------------------------------------------------------
local contourFuncHelp = "Contour(...) requires three or more points or one or more curves."

function Contour(...)
	if (select("#",...) < 1) then
		error("Unrecognized arguments of Contour(...) function. "..contourFuncHelp)
		return nil
	end
	
	firstArg = select(1, ...)
	local argtype = type(firstArg)
	
	if(argtype == "userdata") then
		if (firstArg.type == "Point") then
			points = PointArray()
			for key,value in pairs {...} do 
				points:add(value)
			end
			return ContourByPoints(points)
		elseif (firstArg.type == "Curve") then
			curves = CurveArray()
			for key,value in pairs {...} do 
				curves:add(value)
			end
			return ContourByCurves(curves)
		end
	end
		
	error("Unrecognized arguments of Contour(...) function. "..contourFuncHelp)
	return nil
end

return Geometry2DLib