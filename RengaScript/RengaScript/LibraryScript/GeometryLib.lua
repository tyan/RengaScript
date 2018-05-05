local GeometryLib = {}

-----------------------------------------------------------------------
-- Type check
-----------------------------------------------------------------------

function isNumber(number)
	return type(number) == "number"
end

function isPoint(point)
	return type(point) == "userdata" and point.type == "Point"
end

function isPoint3D(point)
	return type(point) == "userdata" and point.type == "Point3D"
end

function isCurve(curve)
	return type(curve) == "userdata" and curve.type == "Curve"
end

-----------------------------------------------------------------------
-- Args check
-----------------------------------------------------------------------

function thereIsOnePoint3D(...)
	return select("#", ...) == 1 and isPoint3D(...)
end

function thereAre4Numbers(...)
	if select("#", ...) ~= 4 then
		return false
	end
	return isNumber(select(1, ...)) and isNumber(select(2, ...)) and isNumber(select(3, ...)) and isNumber(select(4, ...))
end

function thereAre2Points(...)
	if select("#", ...) ~= 2 then
		return false
	end
	return isPoint(select(1, ...)) and isPoint(select(2, ...))
end

function thereAre3Points3D(...)
	if select("#", ...) ~= 3 then
		return false
	end
	return isPoint3D(select(1, ...)) and isPoint3D(select(2, ...)) and isPoint3D(select(3, ...))
end

function thereAreOnlyPoints(...)
	if select("#", ...) < 1 then
		return false
	end
	for key,value in pairs {...} do 
		if not isPoint(value) then
			return false
		end
	end
	return true
end

function thereAreOnlyCurves(...)
	if select("#", ...) < 1 then
		return false
	end
	for key,value in pairs {...} do 
		if not isCurve(value) then
			return false
		end
	end
	return true
end

-----------------------------------------------------------------------
-- Rect function
-----------------------------------------------------------------------
local rectFuncHelp = "Rect(...) requires 4 numbers or two points."

function Rect(...)
	if thereAre4Numbers(...) then
		return RectByCoord(...)
	elseif thereAre2Points(...) then
		return RectByPoint(...)
	end
	error("Unrecognized arguments of Rect(...) function. "..rectFuncHelp)
	return nil
end


-----------------------------------------------------------------------
-- LineSegment function
-----------------------------------------------------------------------
local lineSegmentFuncHelp = "LineSegment(...) requires 4 numbers or two points."

function LineSegment(...)
	if thereAre4Numbers(...) then
		return LineSegmentByCoord(...)
	elseif thereAre2Points(...) then
		return LineSegmentByPoint(...)
	end
	error("Unrecognized arguments of LineSegment(...) function. "..lineSegmentFuncHelp)
	return nil
end

-----------------------------------------------------------------------
-- Contour function
-----------------------------------------------------------------------
local contourFuncHelp = "Contour(...) requires three or more points or one or more curves."

function Contour(...)
	if thereAreOnlyPoints(...) then
		points = PointArray()
		for key,value in pairs {...} do 
			points:add(value)
		end
		return ContourByPoints(points)
	elseif thereAreOnlyCurves(...) then
		curves = CurveArray()
		for key,value in pairs {...} do 
			curves:add(value)
		end
		return ContourByCurves(curves)
	end
		
	error("Unrecognized arguments of Contour(...) function. "..contourFuncHelp)
	return nil
end

-----------------------------------------------------------------------
-- LCS function
-----------------------------------------------------------------------
local LCSFuncHelp = "LCS(...) requires one point as origin or three points as origin, x axis vector, y axis vector."

function LCS(...)
	if thereIsOnePoint3D(...) then
		return LCSByPoint(...)
	end
	if thereAre3Points3D(...) then
		return LCSBy3Points(...)
	end
		
	error("Unrecognized arguments of LCS(...) function. "..LCSFuncHelp)
	return nil
end

return GeometryLib