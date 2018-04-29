#include <RengaScript/GeometryTypes.h>

namespace renga_script
{
  ////////////////////////////////////////////////////////
  // Point2D
  ////////////////////////////////////////////////////////

  static const double sc_metricPrecise = 0.00000001;

  Point2D::Point2D(double x_, double y_)
    : x(x_), y(y_)
  {}

  bool Point2D::operator==(const Point2D& other) const
  {
    if (fabs(other.x - x) < sc_metricPrecise)
      return fabs(other.y - y) < sc_metricPrecise;
    else
      return false;
  }
}
