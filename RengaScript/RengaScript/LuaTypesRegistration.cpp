#include "LuaTypesRegistration.h"
#include "LuaScriptRuntimeContext.h"
#include "StringConvertion.h"
#include "GeometryTypeWrapper.h"

#include <RengaScript/IParameters.h>
#include <RengaScript/IGeometryBuilder.h>
#include <RengaScript/IObject3DDefinition.h>

#include <assert.h>

#include <lua.hpp>

#include <LuaBridge.h>


using namespace renga_script;

namespace lua
{
  MetricParameter createMetricParameter(
    char const* name, 
    double defaultValue, 
    char const* categories,
    lua_State * pLuaState)
  {
    std::wstring paramName = convertString(name);
    double paramValue = defaultValue;
    std::wstring paramCategories = convertString(categories);

    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pParameters = pContext->getParameters();
    if (pParameters == nullptr)
      throw L"Parameters interface is not supported!";

    MetricParameter result(paramName, paramValue, paramCategories);
    bool parameterWasSet = pParameters->setParameter(result);
    if (parameterWasSet == false)
      throw std::wstring(L"Failed to set parameter: ") + paramName;

    return result;
  }

  void registerParametersTypes(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <MetricParameter>("MetricParameterClass")
      .addProperty("value", &MetricParameter::value, &MetricParameter::setValue)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("CreateMetricParameter", createMetricParameter);
  }

  renga_script::IGeometryBuilder* getGeometryBuilder(lua_State * pLuaState) noexcept(false)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometryBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return pGeometry2DBuilder;
  }

  renga_script::IObject3DDefinition* getObject3DDefinition(lua_State * pLuaState) noexcept(false)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pObject3DDefinition = pContext->getObject3DDefinition();
    if (pObject3DDefinition == nullptr)
      throw L"Object3D definition interface is not supported!";

    return pObject3DDefinition;
  }

  Curve2DWrapper rectConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createRect(Point2D(lbx, lby), Point2D(rtx, rty)));
  }

  Curve2DWrapper rectConstructByPoints(const Point2DWrapper& lb, const Point2DWrapper& rt, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createRect(lb.m_point, rt.m_point));
  }

  Curve2DWrapper lineSegmentConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createLineSegment(Point2D(lbx, lby), Point2D(rtx, rty)));
  }

  Curve2DWrapper lineSegmentConstructByPoints(const Point2DWrapper& lb, const Point2DWrapper& rt, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createLineSegment(lb.m_point, rt.m_point));
  }

  Curve2DWrapper circleConstructByCenterAndRadius(
    const Point2DWrapper& c,
    double r,
    lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createArc(c.m_point, r));
  }

  Curve2DWrapper arcConstructByCenterAndTwoPoints(
    const Point2DWrapper& c, 
    const Point2DWrapper& p1, 
    const Point2DWrapper& p2, 
    int sense,
    lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createArc(c.m_point, p1.m_point, p2.m_point, sense));
  }

  Curve2DWrapper contourConstructByPoints(const Point2DVectorWrapper& points, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createContour(points.getVector()));
  }

  Curve2DWrapper contourConstructByCurves(const CurveVectorWrapper& curves, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createContour(curves.getCurves()));
  }

  Curve3DWrapper lineSegment3DConstructByPoints(const Point3DWrapper& p1, const Point3DWrapper& p2, lua_State * pLuaState)
  {
    auto pGeometryBuilder = getGeometryBuilder(pLuaState);
    return Curve3DWrapper(pGeometryBuilder->createLineSegment3D(p1.m_point, p2.m_point));
  }

  Curve3DWrapper arc3DConstructBy3Points(
    const Point3DWrapper& p1, 
    const Point3DWrapper& p2, 
    const Point3DWrapper& p3, 
    lua_State * pLuaState)
  {
    auto pGeometryBuilder = getGeometryBuilder(pLuaState);
    return Curve3DWrapper(pGeometryBuilder->createArc3D(p1.m_point, p2.m_point, p3.m_point));
  }

  SolidWrapper createCuboid(const Point3DWrapper& p1, const Point3DWrapper& p2, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return SolidWrapper(pGeometry2DBuilder->createCuboid(p1.m_point, p2.m_point));
  }

  Curve3DWrapper contour3DConstructByCurves(const Curve3DVectorWrapper& curves, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return Curve3DWrapper(pGeometry2DBuilder->createContour3D(curves.getCurves()));
  }

  SolidWrapper createExtrusionSolid(const Curve2DWrapper& base, double from, double to, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return SolidWrapper(pGeometry2DBuilder->createExtrusion(base.curve(), from, to));
  }

  SolidWrapper createRevolutionSolid(const Curve2DWrapper& base, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return SolidWrapper(pGeometry2DBuilder->createRevolution(base.curve()));
  }

  LCSWrapper createLCSBy3Points(const Point3DWrapper& origin, const Point3DWrapper& xAxis, const Point3DWrapper& yAxis, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return LCSWrapper(pGeometry2DBuilder->createLCS(origin.m_point, xAxis.m_point, yAxis.m_point));
  }

  LCSWrapper createLCSByPoint(const Point3DWrapper& origin, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    return LCSWrapper(pGeometry2DBuilder->createLCS(origin.m_point));
  }

  void moveSolidToLCS(SolidWrapper& solid, const LCSWrapper& lcs, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    pGeometry2DBuilder->move(solid.solid(), lcs.lcs());
  }

  void dumpCurve(const Curve2DWrapper& curve, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    pGeometry2DBuilder->dump(curve.curve());
  }

  void dumpSolid(const SolidWrapper& solid, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometryBuilder(pLuaState);
    pGeometry2DBuilder->dump(solid.solid());
  }

  void registerGeometryTypes(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Point2DWrapper>("Point")
      .addConstructor<void(*) (double, double)>()
      .addProperty("type", &Point2DWrapper::type)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Point3DWrapper>("Point3D")
      .addConstructor<void(*) (double, double, double)>()
      .addProperty("type", &Point3DWrapper::type)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <LCSWrapper>("LCSClass")
      .addProperty("type", &LCSWrapper::type)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass<Point2DVectorWrapper>("PointArray")
      .addConstructor<void(*) ()>()
      .addFunction("add", &Point2DVectorWrapper::add)
      .addFunction("count", &Point2DVectorWrapper::count)
      .addFunction("get", &Point2DVectorWrapper::get)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Curve2DWrapper>("Curve2DClass")
      .addProperty("type", &Curve2DWrapper::type)
      .addFunction("__add", &Curve2DWrapper::operator+)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass<CurveVectorWrapper>("CurveArray")
      .addConstructor<void(*) ()>()
      .addFunction("add", &CurveVectorWrapper::add)
      .addFunction("count", &CurveVectorWrapper::count)
      .addFunction("get", &CurveVectorWrapper::get)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Curve3DWrapper>("Curve3DClass")
      .addProperty("type", &Curve3DWrapper::type)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass<Curve3DVectorWrapper>("Curve3DArray")
      .addConstructor<void(*) ()>()
      .addFunction("add", &Curve3DVectorWrapper::add)
      .addFunction("count", &Curve3DVectorWrapper::count)
      .addFunction("get", &Curve3DVectorWrapper::get)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <SolidWrapper>("SolidClass")
      .addProperty("type", &SolidWrapper::type)
      .addFunction("__add", &SolidWrapper::operator+)
      .addFunction("__band", &SolidWrapper::operator&)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("RectByCoord", rectConstructByCoord)
      .addFunction("RectByPoint", rectConstructByPoints)
      .addFunction("LineSegmentByCoord", lineSegmentConstructByCoord)
      .addFunction("LineSegmentByPoint", lineSegmentConstructByPoints)
      .addFunction("CircleByCenterAndRadius", circleConstructByCenterAndRadius)
      .addFunction("ArcByCenterAndTwoPoints", arcConstructByCenterAndTwoPoints)
      .addFunction("ContourByPoints", contourConstructByPoints)
      .addFunction("ContourByCurves", contourConstructByCurves)
      .addFunction("LineSegment3DByPoint", lineSegment3DConstructByPoints)
      .addFunction("Arc3DBy3Points", arc3DConstructBy3Points)
      .addFunction("Contour3DByCurves", contour3DConstructByCurves)
      .addFunction("Cuboid", createCuboid)
      .addFunction("Extrusion", createExtrusionSolid)
      .addFunction("Revolution", createRevolutionSolid)
      .addFunction("LCSBy3Points", createLCSBy3Points)
      .addFunction("LCSByPoint", createLCSByPoint)
      .addFunction("Move", moveSolidToLCS)
      .addFunction("DumpCurve", dumpCurve)
      .addFunction("DumpSolid", dumpSolid);
  }

  void setObject3DRepresentation(const SolidWrapper& solid, lua_State * pLuaState)
  {
    auto pObject3DDefinition = getObject3DDefinition(pLuaState);
    pObject3DDefinition->setSolidRepresentation(solid.solid());
  }

  void registerObject3DTypes(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("SetObject3DRepresentation", setObject3DRepresentation);
  }
}
