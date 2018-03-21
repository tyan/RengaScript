#pragma once
#include <RengaScript/GeometryTypes2D.h>

namespace renga_script
{
  class IGeometry2DBuilder
  {
  public:
    virtual ICurve2D* createRect(const Point2D& lb, const Point2D& rt) const = 0;
  };
}
