local ParameterLib = {}

-----------------------------------------------------------------------
-- Metric parameter construc function
-----------------------------------------------------------------------
local metricParameterFuncHelp = "MetricParameter(name, defaultValue, [categories])"
local metricParameterInvalidArgsMsg = "Unrecognized arguments of MetricParameter function. "..metricParameterFuncHelp

function CheckMetricParameterArgs(...)
	if select("#", ...) < 2 then
		return false
	end
	if not isString(select(1, ...)) or not isNumber(select(2, ...)) then
		return false
	end
	return true
end

function MetricParameter(...)
	if CheckMetricParameterArgs(...) then
		if select("#", ...) == 2 then
			return CreateMetricParameter(select(1, ...), select(2, ...), "")
		end
		
		if select("#", ...) == 3 then
			return CreateMetricParameter(select(1, ...), select(2, ...), select(3, ...))
		end
	end
		
	error(metricParameterInvalidArgsMsg)
	return nil
end

return ParameterLib