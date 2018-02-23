#include "LuaTypesRegistration.h"
#include "LuaScriptRuntimeContext.h"
#include "StringConvertion.h"

#include <RengaScript/IParametersService.h>

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
    throw L"Parameters servise not supported!";

  MetricParameter result(paramName, paramValue);
  bool parameterWasSet = pParameters->setParameter(result);
  if (parameterWasSet == false)
    throw std::wstring(L"Failed to set parameter: ") + paramName;

  return result;
}

void lua::registerParameterType(lua_State * pLuaState)
{
  luabridge::getGlobalNamespace(pLuaState)
    .beginClass <renga_script::MetricParameter>("MetricParameterClass")
    .endClass();

  luabridge::getGlobalNamespace(pLuaState)
    .addFunction("MetricParameter", metricParameterConstruct);
}