#pragma once
#include <RengaScript/GeometryTypes2D.h>

namespace renga_script
{
  class IGeometry2DBuilder
  {
  public:
    virtual IRect* createRect(double lbx, double lby, double rtx, double rty) = 0;
  };
}
