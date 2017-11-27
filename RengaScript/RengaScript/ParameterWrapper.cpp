#include "ParameterWrapper.h"
#include "RuntimeContext.h"
#include "StringConvertion.h"

#include <assert.h>

#include <lua.hpp>

#include <LuaBridge.h>

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

  m_parameter = std::make_shared<renga_script::MetricParameter>(paramName, paramValue);

  auto pContext = RuntimeContext::getContext(pLuaState);
  assert(pContext != nullptr);
  pContext->params()[paramName] = m_parameter;
}
