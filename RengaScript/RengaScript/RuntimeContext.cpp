#include "RuntimeContext.h"
#include "Parameter.h"
#include "ParameterWrapper.h"
#include "ScriptData.h"

#include <assert.h>

std::map<lua_State*, RuntimeContext*> RuntimeContext::m_registry;

RuntimeContext::RuntimeContext(lua_State* pLuaState, ScriptData& data)
  : m_pLuaState(pLuaState)
  , m_data(data)
{
  assert(m_pLuaState != nullptr);
  m_registry.insert(std::make_pair(m_pLuaState, this));

  MetricParameterWrapper::RegisterType(m_pLuaState);
}

RuntimeContext::~RuntimeContext()
{
  m_registry.erase(m_pLuaState);
}

renga_script::MetricParameter * RuntimeContext::addMetricParameter(const std::wstring & name, double value)
{
  auto metricParameter = std::make_shared<renga_script::MetricParameter>(name, value);
  m_data.m_parameters.push_back(metricParameter);
  return metricParameter.get();
}

RuntimeContext * RuntimeContext::getContext(lua_State * pLuaState)
{
  return m_registry.at(pLuaState);
}
