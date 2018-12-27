#pragma once

#include <RengaScript/ApiDefines.h>

#include <string>
#include <vector>

namespace renga_script
{
  class RENGA_SCRIPT_EXTERNAL Point2D
  {
  public:
    Point2D() = default;
    Point2D(double x_, double y_);

    bool operator==(const Point2D& other) const;

    double x = 0.0;
    double y = 0.0;
  };

  typedef std::vector<Point2D> Point2DVector;

  class RENGA_SCRIPT_EXTERNAL Point3D
  {
  public:
    Point3D() = default;
    Point3D(double x_, double y_, double z_);

    bool operator==(const Point3D& other) const;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };

  class ILCS
  {
  public:
    virtual ~ILCS() {}
    virtual ILCS* copy() const = 0;
  };

  class ICurve2D
  {
  public:
    virtual ~ICurve2D() {};
    virtual ICurve2D* copy() const = 0;
    virtual ICurve2D* getUnionWith(const ICurve2D* pOther) const = 0;
  };

  typedef std::vector<ICurve2D*> CurveVector;
  typedef std::vector<const ICurve2D*> ConstCurveVector;

  class ICurve3D
  {
  public:
    virtual ~ICurve3D() {};
    virtual ICurve3D* copy() const = 0;
  };

  typedef std::vector<ICurve3D*> Curve3DVector;
  typedef std::vector<const ICurve3D*> ConstCurve3DVector;

  class ISolid
  {
  public:
    virtual ~ISolid() {}
    virtual ISolid* copy() const = 0;
    virtual ISolid* getMultisolidWith(const ISolid* pOther) const = 0;
    virtual ISolid* getUnionWith(const ISolid* pOther) const = 0;
    virtual ISolid* getDifferenceWith(const ISolid* pOther) const = 0;
  };
}
