mockmodule = require "Geometry2DBuilderMock"
testmodule = require "Geometry2DLib"

function TestCallRectByCoord()
	local testResult = Rect(0, 0, 300, 500)
	if (testResult == "RectByCoord(0, 0, 300, 500)") then
		print("Passed: TestCallRectByCoord")
	else
		print("Failed: TestCallRectByCoord, returned: "..testResult)	
	end
end

TestCallRectByCoord()

