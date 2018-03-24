#pragma once
#include <RengaScript/IGeometry2DBuilder.h>

class Geometry2DBuilderMock : public IGeometry2DBuilder
{
public:
  MOCK_CONST_METHOD2(createRect, ICurve2D*(const Point2D& lb, const Point2D& rt));
  MOCK_CONST_METHOD2(createLineSegment, ICurve2D* (const Point2D& p1, const Point2D& p2));
  MOCK_CONST_METHOD1(createContour, ICurve2D* (const PointVector& points));
};

typedef NiceMock<Geometry2DBuilderMock> Geometry2DBuilderNice;
typedef StrictMock<Geometry2DBuilderMock> Geometry2DBuilderStrict;
