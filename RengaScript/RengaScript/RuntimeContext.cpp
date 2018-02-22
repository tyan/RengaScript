#include "RuntimeContext.h"
#include <RengaScript/Parameter.h>

#include "ParameterWrapper.h"

#include <assert.h>

using namespace renga_script;

std::map<lua_State*, RuntimeContext*> RuntimeContext::m_registry;

RuntimeContext::RuntimeContext(lua_State* pLuaState, const Object3DConstructionContext& context)
  : m_pLuaState(pLuaState)
  , m_object3DContext(context)
{
  assert(m_pLuaState != nullptr);
  m_registry.insert(std::make_pair(m_pLuaState, this));

  MetricParameterWrapper::RegisterType(m_pLuaState);
}

RuntimeContext::~RuntimeContext()
{
  m_registry.erase(m_pLuaState);
}

IParametersService * renga_script::RuntimeContext::getParameters() const
{
  return m_object3DContext.pParameters;
}

IGeometryBuilder * renga_script::RuntimeContext::getGeometryBuilder() const
{
  return m_object3DContext.pGeometryBuilder;
}

//renga_script::MetricParameter * RuntimeContext::addMetricParameter(const std::wstring & name, double value)
//{
//  auto metricParameter = std::make_shared<renga_script::MetricParameter>(name, value);
//  m_data.m_parameters.push_back(metricParameter);
//  return metricParameter.get();
//}

RuntimeContext * RuntimeContext::getContext(lua_State * pLuaState)
{
  return m_registry.at(pLuaState);
}
