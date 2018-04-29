#pragma once

#include <RengaScript/GeometryTypes2D.h>

class Curve2DMock : public ICurve2D
{
public:
  MOCK_CONST_METHOD0(copy, ICurve2D*());
};