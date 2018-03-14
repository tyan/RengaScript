#pragma once

namespace renga_script
{
  class Point2D
  {
  public:
    double x;
    double y;
  };

  class ICurve2D
  {
  public:
    virtual ~ICurve2D() {};
    virtual ICurve2D* copy() = 0;
  };
}
