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


  ////////////////////////////////////////////////////////
  // Point3D
  ////////////////////////////////////////////////////////

  Point3D::Point3D(double x_, double y_, double z_)
    : x(x_), y(y_), z(z_)
  {}

  bool Point3D::operator==(const Point3D & other) const
  {
    if (fabs(other.x - x) < sc_metricPrecise)
      if (fabs(other.y - y) < sc_metricPrecise)
        return fabs(other.z - z) < sc_metricPrecise;
    
    return false;
  }
}
