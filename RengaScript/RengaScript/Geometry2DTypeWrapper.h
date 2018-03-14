#pragma once

#include <RengaScript/GeometryTypes2D.h>

namespace lua
{
  class Curve2DWrapper
  {
  public:
    Curve2DWrapper(renga_script::ICurve2D* pCurve);
    Curve2DWrapper(const Curve2DWrapper& other);
    Curve2DWrapper(Curve2DWrapper&& other);
    ~Curve2DWrapper();

  private:
    renga_script::ICurve2D* m_pCurve;
  };
}