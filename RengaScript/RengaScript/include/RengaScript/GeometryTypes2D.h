#pragma once

#include <RengaScript/ApiDefines.h>

#include <string>
#include <vector>

namespace renga_script
{
  class RENGA_SCRIPT_EXTERNAL Point2D
  {
  public:
    Point2D(double x_, double y_);

    std::string type() const;
    bool operator==(const Point2D& other) const;

    double x = 0.0;
    double y = 0.0;
  };

  typedef std::vector<Point2D> PointVector;

  class ICurve2D
  {
  public:
    virtual ~ICurve2D() {};
    virtual ICurve2D* copy() const = 0;
  };
}
