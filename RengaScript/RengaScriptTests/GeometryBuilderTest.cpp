#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "ParametersMock.h"
#include "GeometryBuilderMock.h"
#include "GeometryTypeStub.h"
#include "GeometryTypeMatcher.h"

class LuaGeometryBuilderTest : public Test
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

TEST_F(LuaGeometryBuilderTest, shouldCreateRectByCoordinates)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\Rect200x300.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateRectByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createRect(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\Rect200x300ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateLineSegmentByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\LineSegment_0_0_200_300_ByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateLineSegmentByCoordinates)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLineSegment(Point2D(0, 0), Point2D(200, 300))).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\LineSegment_0_0_200_300_ByCoord.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateCircle)
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

TEST_F(LuaGeometryBuilderTest, shouldCreateArcByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createArc(Point2D(1000, 1000), Point2D(0, 1000), Point2D(2000, 1000), -1)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\ArcByPoints.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateContourByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);

  // expect
  Point2DVector expectedPoints = { Point2D(0, 0), Point2D(300, 300), Point2D(600, 0) };
  EXPECT_CALL(m_geometryBuilderStrict, createContour(expectedPoints)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\ContourByPoints_0_0_300_300_600_0.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateLineSegment3DByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  std::wstring script = L"lineSegment = LineSegment3D(Point3D(0, 0, 0), Point3D(100, 200, 300))";

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLineSegment3D(Point3D(0, 0, 0), Point3D(100, 200, 300))).
    WillOnce(Return(new Curve3DStub()));

  // when
  bool result = executeScriptFromString(script, m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateArc3DByPoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  std::wstring script = L"arc = Arc3D(Point3D(0, 0, 0), Point3D(50, 50, 50), Point3D(100, 100, 0))";

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createArc3D(Point3D(0, 0, 0), Point3D(50, 50, 50), Point3D(100, 100, 0))).
    WillOnce(Return(new Curve3DStub()));

  // when
  bool result = executeScriptFromString(script, m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

Curve3DStub* createCurve3DWithId(std::set<int>& createdCurveIds)
{
  static int curveIndex = 0;
  createdCurveIds.insert(curveIndex++);
  return new Curve3DStub(*createdCurveIds.crbegin());
}

void saveCurve3DIds(const renga_script::ConstCurve3DVector& curves, std::set<int>& curveIds)
{
  for (auto pCurve : curves)
    curveIds.insert(static_cast<const Curve3DStub*>(pCurve)->id);
}

TEST_F(LuaGeometryBuilderTest, shouldCreateContour3DByCurves)
{
  // given
  setUpContext(&m_geometryBuilderNice);

  std::wstring script = 
    L"                                        \
    p1 = Point3D(0, 0, 0)                     \
    p2 = Point3D(300, 300, 300)               \
    p3 = Point3D(600, 600, 0)                 \
                                              \
    side1 = LineSegment3D(p1, p2)             \
    side2 = LineSegment3D(p2, p3)             \
    side3 = LineSegment3D(p3, p1)             \
                                              \
    contour = Contour3D(side1, side2, side3)  \
    ";

  std::set<int> givenCurveIds;
  auto createCurveAction = std::bind(createCurve3DWithId, std::ref(givenCurveIds));
  ON_CALL(m_geometryBuilderNice, createLineSegment3D(_, _)).
    WillByDefault(InvokeWithoutArgs(createCurveAction));

  // expect
  std::set<int> passedCurveIds;
  auto saveCurveIdsAction = std::bind(saveCurve3DIds, std::placeholders::_1, std::ref(passedCurveIds));
  EXPECT_CALL(m_geometryBuilderNice, createContour3D(Matcher<const renga_script::ConstCurve3DVector&>(_))).
    WillOnce(
      DoAll(
        WithArg<0>(Invoke(saveCurveIdsAction)),
        Return(new Curve3DStub())
      )
    );

  // when
  bool result = executeScriptFromString(script, m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_TRUE(givenCurveIds == passedCurveIds);
}

// TODO: create template, remove code duplication for 3D
Curve2DStub* createCurve2DWithId(std::set<int>& createdCurveIds)
{
  static int curveIndex = 0;
  createdCurveIds.insert(curveIndex++);
  return new Curve2DStub(*createdCurveIds.crbegin());
}

void saveCurve2DIds(const renga_script::ConstCurveVector& curves, std::set<int>& curveIds)
{
  for (auto pCurve : curves)
    curveIds.insert(static_cast<const Curve2DStub*>(pCurve)->id);
}

TEST_F(LuaGeometryBuilderTest, shouldCreateContourByCurves)
{
  // given
  setUpContext(&m_geometryBuilderNice);

  std::set<int> givenCurveIds;
  auto createCurveAction = std::bind(createCurve2DWithId, std::ref(givenCurveIds));
  ON_CALL(m_geometryBuilderNice, createLineSegment(_, _)).
    WillByDefault(InvokeWithoutArgs(createCurveAction));

  // expect
  std::set<int> passedCurveIds;
  auto saveCurveIdsAction = std::bind(saveCurve2DIds, std::placeholders::_1, std::ref(passedCurveIds));
  EXPECT_CALL(m_geometryBuilderNice, createContour(Matcher<const renga_script::ConstCurveVector&>(_))).
    WillOnce(
      DoAll(
        WithArg<0>(Invoke(saveCurveIdsAction)),
        Return(new Curve2DStub())
      )
    );

  // when
  bool result = executeLuaScript(L".\\TestData\\ContourByCurves_0_0_300_300_600_0.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_TRUE(givenCurveIds == passedCurveIds);
}

TEST_F(LuaGeometryBuilderTest, shouldCreateCurvesUnion)
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
  bool result = executeLuaScript(L".\\TestData\\CurvesUnion.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 3); // 1 + 2
}

TEST_F(LuaGeometryBuilderTest, shouldCreateCuboid)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  renga_script::Point3D p1(-100, -100, 0), p2(100, 100, 100);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createCuboid(p1, p2)).
    WillOnce(Return(new SolidStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\Cuboid_m100_m100_0_100_100_100.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateExtrusionByCurve)
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
  bool result = executeLuaScript(L".\\TestData\\Extrusion_m100_100.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateRevolutionByCurve)
{
  // given
  setUpContext(&m_geometryBuilderNice);
  std::wstring script =
    L"                                                            \
    base = Contour(Point(0, -100), Point(200, 0), Point(0, 100))  \
    ext = Revolution(base)                                        \
    ";

  int curveId = 42;
  ON_CALL(m_geometryBuilderNice, createContour(Matcher<const renga_script::Point2DVector&>(_))).
    WillByDefault(Return(new Curve2DStub(curveId)));

  // expect
  EXPECT_CALL(m_geometryBuilderNice, createRevolution(CurveIdEqConst(curveId))).
    WillOnce(Return(new SolidStub()));

  // when
  bool result = executeScriptFromString(script, m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateLCSByOnePoint)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  renga_script::Point3D origin(100.0, 0.0, 0.0);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLCS(origin)).
    WillOnce(Return(new LCSStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\LCSByPoint.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateLCSByThreePoints)
{
  // given
  setUpContext(&m_geometryBuilderStrict);
  renga_script::Point3D origin(0.0, 0.0, 0.0), xAxis(0.0, 1.0, 0.0), yAxis(1.0, 0.0, 0.0);

  // expect
  EXPECT_CALL(m_geometryBuilderStrict, createLCS(origin, xAxis, yAxis)).
    WillOnce(Return(new LCSStub()));

  // when
  bool result = executeLuaScript(L".\\TestData\\LCSBy3Points.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldMoveSolidToLCS)
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
  bool result = executeLuaScript(L".\\TestData\\MoveBodyToLCS.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
}

TEST_F(LuaGeometryBuilderTest, shouldCreateMultiSolid)
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
  bool result = executeLuaScript(L".\\TestData\\SolidsCombining.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 30); // (1 + 2) * 10
}

TEST_F(LuaGeometryBuilderTest, shouldCreateSolidsUnion)
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
  bool result = executeLuaScript(L".\\TestData\\SolidsUnion.lua", m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 2); // 1, 2
  EXPECT_EQ(resultId, 3); // 1 + 2
}

TEST_F(LuaGeometryBuilderTest, shouldCreateSolidsDifference)
{
  // given
  setUpContext(&m_geometryBuilderNice);
  int counter = 10;
  int resultId = 0;

  std::wstring script =
    L"                                                            \
    body1 = Cuboid(Point3D(0, 0, 0), Point3D(100, 100, 100))      \
    body2 = Cuboid(Point3D(50, 50, 50), Point3D(200, 200, 200))   \
    body3 = body1 - body2                                         \
    Dump(body3)                                                   \
    ";

  ON_CALL(m_geometryBuilderNice, createCuboid(_, _)).
    WillByDefault(InvokeWithoutArgs([&]() { return new SolidStub(--counter); }));
  EXPECT_CALL(m_geometryBuilderNice, dump(Matcher<const ISolid*>(_))).
    WillOnce(WithArg<0>(Invoke([&](const ISolid* pSolid) { resultId = ((const SolidStub*)pSolid)->id; })));

  // when
  bool result = executeScriptFromString(script, m_context);

  // then
  ASSERT_TRUE(result) << m_context.error;
  EXPECT_EQ(counter, 8); // 9, 8
  EXPECT_EQ(resultId, 1); // 9 - 8
}