#pragma once
#include <RengaScript/IGeometry2DBuilder.h>

class Geometry2DBuilderMock : public IGeometry2DBuilder
{
public:
  MOCK_CONST_METHOD2(createRect, ICurve2D*(const Point2D& lb, const Point2D& rt));
};

typedef NiceMock<Geometry2DBuilderMock> Geometry2DBuilderNice;
typedef StrictMock<Geometry2DBuilderMock> Geometry2DBuilderStrict;
