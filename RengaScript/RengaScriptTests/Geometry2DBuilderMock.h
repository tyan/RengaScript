#pragma once
#include <RengaScript/IGeometry2DBuilder.h>

class Geometry2DBuilderMock : public renga_script::IGeometry2DBuilder
{
public:
  MOCK_METHOD4(createRect, renga_script::IRect*(double lbx, double lby, double rtx, double rty));
};

typedef NiceMock<Geometry2DBuilderMock> Geometry2DBuilderNice;
typedef StrictMock<Geometry2DBuilderMock> Geometry2DBuilderStrict;
