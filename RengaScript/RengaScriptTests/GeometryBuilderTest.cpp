#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "ParametersMock.h"
#include "GeometryBuilderMock.h"
#include "GeometryTypeStub.h"
#include "GeometryTypeMatcher.h"

class GeometryBuilderTest : public Test
{
public:
  void setUpGeometryBuilder(IGeometryBuilder* pService)
  {
    m_context.pGeometryBuilder = pService;
  }

  void setUpParameters(IParameters* pService)
  {
    m_context.pParameters = pService;
  }

protected:
  Object3DConstructionContext m_context;
  
  GeometryBuilderStrict m_geometry2DStrictMock;
  GeometryBuilderNice m_geometry2DNiceMock;

  ParametersStrict m_parametersStrictMock;
  ParametersNice m_parametersNiceMock;
};

TEST_F(GeometryBuilderTest, shouldCreateRectByCoordinates)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\Rect200x300.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateRectByPoints)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\Rect200x300ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLineSegmentByPoints)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\LineSegment_0_0_200_300_ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLineSegmentByCoordinates)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\LineSegment_0_0_200_300_ByCoord.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateContourByPoints)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);

  // expect
  PointVector expectedPoints = { Point2D(0, 0), Point2D(300, 300), Point2D(600, 0) };
  EXPECT_CALL(m_geometry2DStrictMock, createContour(expectedPoints)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\ContourByPoints_0_0_300_300_600_0.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

Curve2DStub* createCurveWithId(std::set<int>& createdCurveIds)
{
  static int curveIndex = 0;
  createdCurveIds.insert(curveIndex++);
  return new Curve2DStub(*createdCurveIds.crbegin());
}

void saveCurveIds(const renga_script::ConstCurveVector& curves, std::set<int>& curveIds)
{
  for (auto pCurve : curves)
    curveIds.insert(static_cast<const Curve2DStub*>(pCurve)->id);
}

TEST_F(GeometryBuilderTest, shouldCreateContourByCurves)
{
  // given
  setUpGeometryBuilder(&m_geometry2DNiceMock);

  std::set<int> givenCurveIds;
  auto createCurveAction = std::bind(createCurveWithId, std::ref(givenCurveIds));
  ON_CALL(m_geometry2DNiceMock, createLineSegment(_, _)).
    WillByDefault(InvokeWithoutArgs(createCurveAction));

  // expect
  std::set<int> passedCurveIds;
  auto saveCurveIdsAction = std::bind(saveCurveIds, std::placeholders::_1, std::ref(passedCurveIds));
  EXPECT_CALL(m_geometry2DNiceMock, createContour(Matcher<const renga_script::ConstCurveVector&>(_))).
    WillOnce(
      DoAll(
        WithArg<0>(Invoke(saveCurveIdsAction)),
        Return(new Curve2DStub())
      )
    );

  // when
  bool result = executeScript(L".\\TestData\\ContourByCurves_0_0_300_300_600_0.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_TRUE(givenCurveIds == passedCurveIds);
}

TEST_F(GeometryBuilderTest, shouldCallCurvesAddition)
{
  // given
  setUpGeometryBuilder(&m_geometry2DNiceMock);
  int counter = 0;
  int resultId = 0;

  ON_CALL(m_geometry2DNiceMock, createRect(_, _)).
    WillByDefault(InvokeWithoutArgs([&]() { return new Curve2DStub(++counter); }));
  EXPECT_CALL(m_geometry2DNiceMock, dump(_)).
    WillOnce(WithArg<0>(Invoke([&](const ICurve2D* pCurve) { resultId = ((const Curve2DStub*)pCurve)->id; })));

  // when
  bool result = executeScript(L".\\TestData\\AddCurves.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 3); // 1 + 2
}

TEST_F(GeometryBuilderTest, shouldCreateExtrusionByCurve)
{
  // given
  setUpGeometryBuilder(&m_geometry2DNiceMock);

  int curveId = 42;
  ON_CALL(m_geometry2DNiceMock, createContour(Matcher<const renga_script::PointVector&>(_))).
    WillByDefault(Return(new Curve2DStub(curveId)));

  // expect
  EXPECT_CALL(m_geometry2DNiceMock, createExtrusion(CurveIdEq(curveId), -100, 100)).
    WillOnce(Return(new SolidStub()));

  // when
  bool result = executeScript(L".\\TestData\\Extrusion_m100_100.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLCSByOnePoint)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);
  renga_script::Point3D origin(100.0, 0.0, 0.0);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createLCS(origin)).
    WillOnce(Return(new LCSStub()));

  // when
  bool result = executeScript(L".\\TestData\\LCSByPoint.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLCSByThreePoints)
{
  // given
  setUpGeometryBuilder(&m_geometry2DStrictMock);
  renga_script::Point3D origin(0.0, 0.0, 0.0), xAxis(0.0, 1.0, 0.0), yAxis(1.0, 0.0, 0.0);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createLCS(origin, xAxis, yAxis)).
    WillOnce(Return(new LCSStub()));

  // when
  bool result = executeScript(L".\\TestData\\LCSBy3Points.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}