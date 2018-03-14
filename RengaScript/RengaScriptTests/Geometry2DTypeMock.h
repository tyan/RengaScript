#pragma once

#include <RengaScript/GeometryTypes2D.h>

class Curve2DMock : public renga_script::ICurve2D
{
public:
  MOCK_METHOD0(copy, ICurve2D*());
};