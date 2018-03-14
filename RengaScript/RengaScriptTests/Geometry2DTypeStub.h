#pragma once

#include <RengaScript/GeometryTypes2D.h>

class Curve2DStub : public renga_script::ICurve2D
{
public:
  Curve2DStub()
  {}
  
  renga_script::ICurve2D* copy()
  {
    return new Curve2DStub();
  }
};
