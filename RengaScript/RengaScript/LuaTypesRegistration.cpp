#include "LuaTypesRegistration.h"
#include "LuaScriptRuntimeContext.h"
#include "StringConvertion.h"
#include "Geometry2DTypeWrapper.h"

#include <RengaScript/IParameters.h>
#include <RengaScript/IGeometry2DBuilder.h>

#include <assert.h>

#include <lua.hpp>

#include <LuaBridge.h>


using namespace renga_script;

namespace lua
{

  MetricParameter metricParameterConstruct(char const* name, double defaultValue, lua_State * pLuaState)
  {
    std::wstring paramName = convertString(name);
    double paramValue = defaultValue;

    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pParameters = pContext->getParameters();
    if (pParameters == nullptr)
      throw L"Parameters interface is not supported!";

    MetricParameter result(paramName, paramValue);
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
      .addFunction("MetricParameter", metricParameterConstruct);
  }

  renga_script::IGeometry2DBuilder* getGeometry2DBuilder(lua_State * pLuaState) noexcept(false)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return pGeometry2DBuilder;
  }

  Curve2DWrapper rectConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometry2DBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createRect(Point2D(lbx, lby), Point2D(rtx, rty)));
  }

  Curve2DWrapper rectConstructByPoints(const Point2D& lb, const Point2D& rt, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometry2DBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createRect(lb, rt));
  }

  Curve2DWrapper lineSegmentConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometry2DBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createLineSegment(Point2D(lbx, lby), Point2D(rtx, rty)));
  }

  Curve2DWrapper lineSegmentConstructByPoints(const Point2D& lb, const Point2D& rt, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometry2DBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createLineSegment(lb, rt));
  }

  Curve2DWrapper contourConstructByPoints(const Point2DVectorWrapper& points, lua_State * pLuaState)
  {
    auto pGeometry2DBuilder = getGeometry2DBuilder(pLuaState);
    return Curve2DWrapper(pGeometry2DBuilder->createContour(points.getVector()));
  }

  void registerGeometry2DTypes(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Point2D>("Point")
      .addConstructor<void(*) (double, double)>()
      .addProperty("type", &Point2D::type)
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
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("RectByCoord", rectConstructByCoord)
      .addFunction("RectByPoint", rectConstructByPoints);

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("LineSegmentByCoord", lineSegmentConstructByCoord)
      .addFunction("LineSegmentByPoint", lineSegmentConstructByPoints)
      .addFunction("ContourByPoints", contourConstructByPoints);
  }
}
