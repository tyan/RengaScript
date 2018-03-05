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
  };

  class IRect : public ICurve2D
  {
  public:
  };
}
