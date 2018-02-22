#include "ParameterWrapper.h"
#include "RuntimeContext.h"
#include "StringConvertion.h"

#include <RengaScript/IParametersService.h>

#include <assert.h>

#include <lua.hpp>

#include <LuaBridge.h>

using namespace renga_script;

void MetricParameterWrapper::RegisterType(lua_State * pLuaState)
{
  luabridge::getGlobalNamespace(pLuaState)
    .beginClass <MetricParameterWrapper>("MetricParameter")
    .addConstructor<void(*) (char const*, double, lua_State *)>()
    .endClass();
}

MetricParameterWrapper::MetricParameterWrapper(char const* name, double defaultValue, lua_State * pLuaState)
{
  std::wstring paramName = convertString(name);
  double paramValue = defaultValue;

  auto pContext = RuntimeContext::getContext(pLuaState);
  assert(pContext != nullptr);
  
  auto pParameters = pContext->getParameters();
  if (pParameters == nullptr)
    throw "Parameters functionality not supported!";

  m_pImp = std::make_unique<renga_script::MetricParameter>(paramName, paramValue);
  pParameters->setParameter(*m_pImp);
}
