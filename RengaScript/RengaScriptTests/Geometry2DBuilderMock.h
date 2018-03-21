#pragma once
#include <RengaScript/IGeometry2DBuilder.h>

class Geometry2DBuilderMock : public renga_script::IGeometry2DBuilder
{
public:
  MOCK_METHOD4(createRect, renga_script::ICurve2D*(double lbx, double lby, double rtx, double rty));
  MOCK_METHOD2(createRect, renga_script::ICurve2D*(const renga_script::Point2D& lb, const renga_script::Point2D& rt));
};

typedef NiceMock<Geometry2DBuilderMock> Geometry2DBuilderNice;
typedef StrictMock<Geometry2DBuilderMock> Geometry2DBuilderStrict;
