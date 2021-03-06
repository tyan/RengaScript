#pragma once
#include <RengaScript/IGeometryBuilder.h>

class GeometryBuilderMock : public IGeometryBuilder
{
public:
  MOCK_CONST_METHOD2(createRect, ICurve2D*(const Point2D& lb, const Point2D& rt));
  MOCK_CONST_METHOD2(createLineSegment, ICurve2D* (const Point2D& p1, const Point2D& p2));
  MOCK_CONST_METHOD2(createArc, ICurve2D* (const Point2D& c, double r));
  MOCK_CONST_METHOD4(createArc, ICurve2D*(const Point2D& c, const Point2D& p1, const Point2D& p2, int sense));
  MOCK_CONST_METHOD1(createContour, ICurve2D* (const Point2DVector& points));
  MOCK_CONST_METHOD1(createContour, ICurve2D* (const ConstCurveVector& curves));
  MOCK_CONST_METHOD2(createLineSegment3D, ICurve3D*(const Point3D& p1, const Point3D& p2));
  MOCK_CONST_METHOD3(createArc3D, ICurve3D* (const Point3D& p1, const Point3D& p2, const Point3D& p3));
  MOCK_CONST_METHOD1(createContour3D, ICurve3D*(const ConstCurve3DVector& curves));
  MOCK_CONST_METHOD3(createLCS, ILCS*(const Point3D& origin, const Point3D& xAxis, const Point3D& yAxis));
  MOCK_CONST_METHOD1(createLCS, ILCS*(const Point3D& origin));
  MOCK_CONST_METHOD2(createCuboid, ISolid*(const Point3D& p1, const Point3D& p2));
  MOCK_CONST_METHOD1(createRevolution, ISolid* (const ICurve2D* pBase));
  MOCK_CONST_METHOD3(createExtrusion, ISolid* (const ICurve2D* pBase, double from, double to));
  MOCK_CONST_METHOD2(move, void(ISolid* pSolid, const ILCS* pLcs));
  MOCK_CONST_METHOD1(dump, void(const ICurve2D* pCurve));
  MOCK_CONST_METHOD1(dump, void(const ISolid* pSolid));
};

typedef NiceMock<GeometryBuilderMock> GeometryBuilderNice;
typedef StrictMock<GeometryBuilderMock> GeometryBuilderStrict;
