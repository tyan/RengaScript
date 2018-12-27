#pragma once
#include <RengaScript/GeometryTypes.h>

namespace renga_script
{
  class IGeometryBuilder
  {
  public:
    virtual ICurve2D* createRect(const Point2D& lb, const Point2D& rt) const = 0;
    virtual ICurve2D* createLineSegment(const Point2D& p1, const Point2D& p2) const = 0;
    virtual ICurve2D* createArc(const Point2D& c, double r) const = 0;
    virtual ICurve2D* createArc(const Point2D& c, const Point2D& p1, const Point2D& p2, int sense) const = 0;
    virtual ICurve2D* createContour(const Point2DVector& points) const = 0;
    virtual ICurve2D* createContour(const ConstCurveVector& curves) const = 0;
    virtual ILCS* createLCS(const Point3D& origin) const = 0;
    virtual ILCS* createLCS(const Point3D& origin, const Point3D& xAxis, const Point3D& yAxis) const = 0;
    virtual ISolid* createCuboid(const Point3D& p1, const Point3D& p2) const = 0;
    virtual ISolid* createExtrusion(const ICurve2D* pBase, double from, double to) const = 0;
    virtual void move(ISolid* pSolid, const ILCS* pLcs) const = 0;
    virtual void dump(const ICurve2D* pCurve) const = 0;
    virtual void dump(const ISolid* pSolid) const = 0;
  };
}
