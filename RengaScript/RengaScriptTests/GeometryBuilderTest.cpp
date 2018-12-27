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
  void setUpContext(IGeometryBuilder* pGeometryBuilder)
  {
    m_context.pGeometryBuilder = pGeometryBuilder;
  }

protected:
  Object3DConstructionContext m_context;
  
  GeometryBuilderStrict m_geometryBuilderStrict;
  GeometryBuilderNice m_geometryBuilderNice;
};

TEST_F(GeometryBuilderTest, shouldCreateRectByCoordinates)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\Rect200x300.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateRectByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\Rect200x300ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLineSegmentByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\LineSegment_0_0_200_300_ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLineSegmentByCoordinates)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\LineSegment_0_0_200_300_ByCoord.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateCircle)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  std::wstring script = L"arc = Arc(Point(1000, 1000), 1000)";

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createArc(Point2D(1000, 1000), 1000)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScriptFromString(script, m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateArcByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createArc(Point2D(1000, 1000), Point2D(0, 1000), Point2D(2000, 1000), -1)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeScript(L".\\TestData\\ArcByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateContourByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  Point2DVector expectedPoints = { Point2D(0, 0), Point2D(300, 300), Point2D(600, 0) };
  EXPECT_CALL(m_geometryBuilderStrict, createContour(expectedPoints)).
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
  setUpContext(&m_geometryBuilderNice);

  std::set<int> givenCurveIds;
  auto createCurveAction = std::bind(createCurveWithId, std::ref(givenCurveIds));
  ON_CALL(m_geometryBuilderNice, createLineSegment(_, _)).
    WillByDefault(InvokeWithoutArgs(createCurveAction));

  // expect
  std::set<int> passedCurveIds;
  auto saveCurveIdsAction = std::bind(saveCurveIds, std::placeholders::_1, std::ref(passedCurveIds));
  EXPECT_CALL(m_geometryBuilderNice, createContour(Matcher<const renga_script::ConstCurveVector&>(_))).
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

TEST_F(GeometryBuilderTest, shouldCreateCurvesUnion)
{
  // given
  setUpContext(&m_geometryBuilderNice);
  int counter = 0;
  int resultId = 0;

  ON_CALL(m_geometryBuilderNice, createRect(_, _)).
    WillByDefault(InvokeWithoutArgs([&]() { return new Curve2DStub(++counter); }));
  EXPECT_CALL(m_geometryBuilderNice, dump(Matcher<const ICurve2D*>(_))).
    WillOnce(WithArg<0>(Invoke([&](const ICurve2D* pCurve) { resultId = ((const Curve2DStub*)pCurve)->id; })));

  // when
  bool result = executeScript(L".\\TestData\\CurvesUnion.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 3); // 1 + 2
}

TEST_F(GeometryBuilderTest, shouldCreateCuboid)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  renga_script::Point3D p1(-100, -100, 0), p2(100, 100, 100);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createCuboid(p1, p2)).
    WillOnce(Return(new SolidStub()));

  // when
  bool result = executeScript(L".\\TestData\\Cuboid_m100_m100_0_100_100_100.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateExtrusionByCurve)
{
  // given
  setUpContext(&m_geometryBuilderNice);

  int curveId = 42;
  ON_CALL(m_geometryBuilderNice, createContour(Matcher<const renga_script::Point2DVector&>(_))).
    WillByDefault(Return(new Curve2DStub(curveId)));

  // expect
  EXPECT_CALL(m_geometryBuilderNice, createExtrusion(CurveIdEqConst(curveId), -100, 100)).
    WillOnce(Return(new SolidStub()));

  // when
  bool result = executeScript(L".\\TestData\\Extrusion_m100_100.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLCSByOnePoint)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  renga_script::Point3D origin(100.0, 0.0, 0.0);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLCS(origin)).
    WillOnce(Return(new LCSStub()));

  // when
  bool result = executeScript(L".\\TestData\\LCSByPoint.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateLCSByThreePoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  renga_script::Point3D origin(0.0, 0.0, 0.0), xAxis(0.0, 1.0, 0.0), yAxis(1.0, 0.0, 0.0);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLCS(origin, xAxis, yAxis)).
    WillOnce(Return(new LCSStub()));

  // when
  bool result = executeScript(L".\\TestData\\LCSBy3Points.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldMoveSolidToLCS)
{
  // given
  setUpContext(&m_geometryBuilderNice);
  int bodyId = 42, lcsId = 142;

  ON_CALL(m_geometryBuilderNice, createCuboid(Point3D(0, 0, 0), Point3D(100, 100, 100))).
    WillByDefault(Return(new SolidStub(bodyId)));
  ON_CALL(m_geometryBuilderNice, createLCS(_)).
    WillByDefault(Return(new LCSStub(lcsId)));

  // expect
  EXPECT_CALL(m_geometryBuilderNice, move(SolidIdEq(bodyId), LCSIdEqConst(lcsId)));

  // when
  bool result = executeScript(L".\\TestData\\MoveBodyToLCS.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(GeometryBuilderTest, shouldCreateMultiSolid)
{
  // given
  setUpContext(&m_geometryBuilderNice);
  int counter = 0;
  int resultId = 0;

  ON_CALL(m_geometryBuilderNice, createCuboid(_, _)).
    WillByDefault(InvokeWithoutArgs([&]() { return new SolidStub(++counter); }));
  EXPECT_CALL(m_geometryBuilderNice, dump(Matcher<const ISolid*>(_))).
    WillOnce(WithArg<0>(Invoke([&](const ISolid* pSolid) { resultId = ((const SolidStub*)pSolid)->id; })));

  // when
  bool result = executeScript(L".\\TestData\\SolidsCombining.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 30); // (1 + 2) * 10
}

TEST_F(GeometryBuilderTest, shouldCreateSolidsUnion)
{
  // given
  setUpContext(&m_geometryBuilderNice);
  int counter = 0;
  int resultId = 0;

  ON_CALL(m_geometryBuilderNice, createCuboid(_, _)).
    WillByDefault(InvokeWithoutArgs([&]() { return new SolidStub(++counter); }));
  EXPECT_CALL(m_geometryBuilderNice, dump(Matcher<const ISolid*>(_))).
    WillOnce(WithArg<0>(Invoke([&](const ISolid* pSolid) { resultId = ((const SolidStub*)pSolid)->id; })));

  // when
  bool result = executeScript(L".\\TestData\\SolidsUnion.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 3); // 1 + 2
}