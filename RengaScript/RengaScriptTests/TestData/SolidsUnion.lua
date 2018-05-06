body1 = Cuboid(Point3D(0, 0, 0), Point3D(100, 100, 100))
body2 = Cuboid(Point3D(100, 100, 100), Point3D(200, 200, 200))
body3 = body1 + body2
Dump(body3)
