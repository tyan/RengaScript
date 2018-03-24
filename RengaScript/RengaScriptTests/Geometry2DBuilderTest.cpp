#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "ParametersMock.h"
#include "Geometry2DBuilderMock.h"
#include "Geometry2DTypeStub.h"

class Geometry2DBuilderTest : public Test
{
public:
  void setUpGeometry2DBuilder(IGeometry2DBuilder* pService)
  {
    m_context.pGeometryBuilder2D = pService;
  }

  void setUpParameters(IParameters* pService)
  {
    m_context.pParameters = pService;
  }

protected:
  Object3DConstructionContext m_context;
  
  Geometry2DBuilderStrict m_geometry2DStrictMock;
  Geometry2DBuilderNice m_geometry2DNiceMock;

  ParametersStrict m_parametersStrictMock;
  ParametersNice m_parametersNiceMock;
};

TEST_F(Geometry2DBuilderTest, shouldCreateRectByCoordinates)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\Rect200x300.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(Geometry2DBuilderTest, shouldCreateRectByPoints)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\Rect200x300ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(Geometry2DBuilderTest, shouldCreateLineSegmentByPoints)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\LineSegment_0_0_200_300_ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(Geometry2DBuilderTest, shouldCreateLineSegmentByCoordinates)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\LineSegment_0_0_200_300_ByCoord.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(Geometry2DBuilderTest, shouldCreateContourByPoints)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  PointVector expectedPoints = { Point2D(0, 0), Point2D(300, 300), Point2D(600, 0) };
  EXPECT_CALL(m_geometry2DStrictMock, createContour(expectedPoints)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\ContourTriangle_0_0_300_300_600_0.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}