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

  void registerMetricParameterType(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <MetricParameter>("MetricParameterClass")
      .addProperty("value", &MetricParameter::value, &MetricParameter::setValue)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("MetricParameter", metricParameterConstruct);
  }

  void registerPoint2D(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Point2D>("Point")
      .addConstructor<void(*) (double, double)>()
      .addProperty("type", &Point2D::type)
      .endClass();
  }

  void registerCurve2DWrapper(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Curve2DWrapper>("Curve2DClass")
      .endClass();
  }

  Curve2DWrapper rectConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return Curve2DWrapper(pGeometry2DBuilder->createRect(Point2D(lbx, lby), Point2D(rtx, rty)));
  }

  Curve2DWrapper rectConstructByPoints(const Point2D& lb, const Point2D& rt, lua_State * pLuaState)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return Curve2DWrapper(pGeometry2DBuilder->createRect(lb, rt));
  }

  void registerRectType(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("RectByCoord", rectConstructByCoord)
      .addFunction("RectByPoint", rectConstructByPoints);
  }

  Curve2DWrapper lineSegmentConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return Curve2DWrapper(pGeometry2DBuilder->createLineSegment(Point2D(lbx, lby), Point2D(rtx, rty)));
  }

  Curve2DWrapper lineSegmentConstructByPoints(const Point2D& lb, const Point2D& rt, lua_State * pLuaState)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return Curve2DWrapper(pGeometry2DBuilder->createLineSegment(lb, rt));
  }

  void registerLineSegmentType(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("LineSegmentByCoord", lineSegmentConstructByCoord)
      .addFunction("LineSegmentByPoint", lineSegmentConstructByPoints);
  }
}
