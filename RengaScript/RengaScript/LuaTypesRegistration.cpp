#include "LuaTypesRegistration.h"
#include "LuaScriptRuntimeContext.h"
#include "StringConvertion.h"

#include <RengaScript/IParameters.h>
#include <RengaScript/IGeometry2DBuilder.h>

#include <assert.h>

#include <lua.hpp>

#include <LuaBridge.h>

using namespace renga_script;

MetricParameter metricParameterConstruct(char const* name, double defaultValue, lua_State * pLuaState)
{
  std::wstring paramName = convertString(name);
  double paramValue = defaultValue;

  auto pContext = lua::ScriptRuntimeContext::getContext(pLuaState);
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

void lua::registerMetricParameterType(lua_State * pLuaState)
{
  luabridge::getGlobalNamespace(pLuaState)
    .beginClass <renga_script::MetricParameter>("MetricParameterClass")
    .endClass();

  luabridge::getGlobalNamespace(pLuaState)
    .addFunction("MetricParameter", metricParameterConstruct);
}

std::shared_ptr<renga_script::IRect> rectConstruct(double lbx, double lby, double rtx, double rty, lua_State * pLuaState)
{
  auto pContext = lua::ScriptRuntimeContext::getContext(pLuaState);
  assert(pContext != nullptr);

  auto pGeometry2DBuilder = pContext->getGeometry2DBuilder();
  if (pGeometry2DBuilder == nullptr)
    throw L"Geometry 2D builder interface is not supported!";

  return std::shared_ptr<renga_script::IRect>(pGeometry2DBuilder->createRect(lbx, lby, rtx, rty));
}

void lua::registerRectType(lua_State * pLuaState)
{
  luabridge::getGlobalNamespace(pLuaState)
    .beginClass <std::shared_ptr<renga_script::IRect>>("RectClass")
    .endClass();

  luabridge::getGlobalNamespace(pLuaState)
    .addFunction("Rect", rectConstruct);
}
