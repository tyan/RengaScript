#pragma once

#include <RengaScript/GeometryTypes2D.h>

class Curve2DStub : public ICurve2D
{
public:
  Curve2DStub()
  {}
  
  ICurve2D* copy() const override
  {
    return new Curve2DStub();
  }
};
