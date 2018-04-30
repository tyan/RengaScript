#pragma once
#include <RengaScript/IGeometryBuilder.h>

class GeometryBuilderMock : public IGeometryBuilder
{
public:
  MOCK_CONST_METHOD2(createRect, ICurve2D*(const Point2D& lb, const Point2D& rt));
  MOCK_CONST_METHOD2(createLineSegment, ICurve2D* (const Point2D& p1, const Point2D& p2));
  MOCK_CONST_METHOD1(createContour, ICurve2D* (const PointVector& points));
  MOCK_CONST_METHOD1(createContour, ICurve2D* (const ConstCurveVector& curves));
  MOCK_CONST_METHOD3(createLCS, ILCS*(const Point3D& origin, const Point3D& xAxis, const Point3D& yAxis));
  MOCK_CONST_METHOD3(createExtrusion, ISolid* (const ICurve2D* pBase, double from, double to));
  MOCK_CONST_METHOD1(dump, void(const ICurve2D* pCurve));
};

typedef NiceMock<GeometryBuilderMock> GeometryBuilderNice;
typedef StrictMock<GeometryBuilderMock> GeometryBuilderStrict;
