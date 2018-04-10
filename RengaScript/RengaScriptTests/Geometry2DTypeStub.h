#pragma once

#include <RengaScript/GeometryTypes2D.h>

class Curve2DStub : public ICurve2D
{
public:
  Curve2DStub()
  {}

  Curve2DStub(int id_)
    : id(id_)
  {}
  
  Curve2DStub(const Curve2DStub&) = default;
  Curve2DStub(Curve2DStub&&) = default;

  ICurve2D* copy() const override
  {
    return new Curve2DStub(id);
  }

public:
  int id = 0;
};
