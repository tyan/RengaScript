anyNumber = 42
base = Contour(Point(-anyNumber, -anyNumber), Point(-anyNumber, anyNumber), Point(anyNumber, anyNumber))
ext = Extrusion(base, -100, 100)