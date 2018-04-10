p1 = Point(0, 0)
p2 = Point(300, 300)
p3= Point(600, 0)

side1 = LineSegment(p1, p2)
side2 = LineSegment(p2, p3)
side3 = LineSegment(p3, p1)

contour = Contour(side1, side2, side3)