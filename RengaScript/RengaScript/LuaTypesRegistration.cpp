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
      .beginClass <renga_script::MetricParameter>("MetricParameterClass")
      .addProperty("value", &renga_script::MetricParameter::value, &renga_script::MetricParameter::setValue)
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("MetricParameter", metricParameterConstruct);
  }

  Curve2DWrapper rectConstructByCoord(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
  {
    auto pContext = ScriptRuntimeContext::getContext(pLuaState);
    assert(pContext != nullptr);

    auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
    if (pGeometry2DBuilder == nullptr)
      throw L"Geometry 2D builder interface is not supported!";

    return Curve2DWrapper(pGeometry2DBuilder->createRect(lbx, lby, rtx, rty));
  }

  void registerRectType(lua_State * pLuaState)
  {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass <Curve2DWrapper>("Curve2DClass")
      .endClass();

    luabridge::getGlobalNamespace(pLuaState)
      .addFunction("RectByCoord", rectConstructByCoord);
  }
}
