local GeometryLib = {}

-----------------------------------------------------------------------
-- Type check
-----------------------------------------------------------------------

function isPoint(point)
	return type(point) == "userdata" and point.type == "Point"
end

function isPoint3D(point)
	return type(point) == "userdata" and point.type == "Point3D"
end

function isCurve(curve)
	return type(curve) == "userdata" and curve.type == "Curve"
end

function isCurve3D(curve)
	return type(curve) == "userdata" and curve.type == "Curve3D"
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

function thereAre2Points3D(...)
	if select("#", ...) ~= 2 then
		return false
	end
	return isPoint3D(select(1, ...)) and isPoint3D(select(2, ...))
end

function thereAre3Points3D(...)
	if select("#", ...) ~= 3 then
		return false
	end
	return isPoint3D(select(1, ...)) and isPoint3D(select(2, ...)) and isPoint3D(select(3, ...))
end

function thereAre3Points2DInFirst3Args(...)
	if select("#", ...) < 3 then
		return false
	end
	return isPoint(select(1, ...)) and isPoint(select(2, ...)) and isPoint(select(3, ...))
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

function thereAreOnlyCurves3D(...)
	if select("#", ...) < 1 then
		return false
	end
	for key,value in pairs {...} do 
		if not isCurve3D(value) then
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
-- Arc function
-----------------------------------------------------------------------
local arcFuncHelp = "Arc(...) requires center, begin point, end point and sense".. 
"(sense > 0 to move from begin point to end point counterclockwise, sense < 0 otherwise) to create circle arc"..
 "or center point and radius to create circle"

function Arc(...)
	if thereAre3Points2DInFirst3Args(...) and isNumber(select(4, ...)) then
		return ArcByCenterAndTwoPoints(...)
  end
  if select("#", ...) == 2 and isPoint(select(1, ...)) and isNumber(select(2, ...)) then
		return CircleByCenterAndRadius(...)
  end
	error("Unrecognized arguments of Arc(...) function. "..arcFuncHelp)
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
-- LineSegment3D function
-----------------------------------------------------------------------
local lineSegment3DFuncHelp = "LineSegment3D(...) requires two points."

function LineSegment3D(...)
	if thereAre2Points3D(...) then
		return LineSegment3DByPoint(...)
	end
	error("Unrecognized arguments of LineSegment3D(...) function. "..lineSegment3DFuncHelp)
	return nil
end

-----------------------------------------------------------------------
-- Arc3D function
-----------------------------------------------------------------------
local arc3DFuncHelp = "Arc3D(...) requires three points"

function Arc3D(...)
	if thereAre3Points3D(...) then
		return Arc3DBy3Points(...)
  end
	error("Unrecognized arguments of Arc3D(...) function. "..arc3DFuncHelp)
	return nil
end

-----------------------------------------------------------------------
-- Contour3D function
-----------------------------------------------------------------------
local contour3DFuncHelp = "Contour3D(...) requires one or more 3D curves."

function Contour3D(...)
	if thereAreOnlyCurves3D(...) then
		curves = Curve3DArray()
		for key,value in pairs {...} do 
			curves:add(value)
		end
		return Contour3DByCurves(curves)
	end
		
	error("Unrecognized arguments of Contour3D(...) function. "..contour3DFuncHelp)
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