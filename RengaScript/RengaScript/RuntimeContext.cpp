#include "RuntimeContext.h"
#include "Parameter.h"
#include "ParameterWrapper.h"

#include <lua.hpp>

std::map<lua_State*, RuntimeContext*> RuntimeContext::m_registry;

RuntimeContext::RuntimeContext()
  : m_pLuaState(nullptr)
{
  m_pLuaState = luaL_newstate();   /* opens Lua */
  luaL_openlibs(m_pLuaState);      /* opens the basic library */

  m_registry.insert(std::make_pair(m_pLuaState, this));

  MetricParameterWrapper::RegisterType(m_pLuaState);
}

RuntimeContext::~RuntimeContext()
{
  m_registry.erase(m_pLuaState);

  lua_close(m_pLuaState);
}

lua_State * RuntimeContext::getLua()
{
  return m_pLuaState;
}

renga_script::MetricParameter * RuntimeContext::addMetricParameter(const std::wstring & name, double value)
{
  auto metricParameter = std::make_shared<renga_script::MetricParameter>(name, value);
  m_params.push_back(metricParameter);
  return metricParameter.get();
}

size_t RuntimeContext::parametersCount() const
{
  return m_params.size();
}

renga_script::AbstractParameter * RuntimeContext::getParameter(size_t index) const
{
  return m_params.at(index).get();
}

RuntimeContext * RuntimeContext::getContext(lua_State * pLuaState)
{
  return m_registry.at(pLuaState);
}
