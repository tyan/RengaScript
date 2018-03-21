#pragma once

#include <string>

namespace renga_script
{
  class Point2D
  {
  public:
    Point2D(double x_, double y_)
      : x(x_), y(y_)
    {}

    std::string type() const
    {
      return "Point2D";
    }

    double x = 0.0;
    double y = 0.0;
  };

  class ICurve2D
  {
  public:
    virtual ~ICurve2D() {};
    virtual ICurve2D* copy() = 0;
  };
}
