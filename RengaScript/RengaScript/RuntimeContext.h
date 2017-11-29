#pragma once
#include <list>
#include <map>
#include <memory>

struct lua_State;

namespace renga_script
{
  class AbstractParameter;
  class MetricParameter;
}

class RuntimeContext
{
public:
  RuntimeContext();
  ~RuntimeContext();

  lua_State* getLua();
  renga_script::MetricParameter* addMetricParameter(const std::wstring& name, double value);

public:
  static RuntimeContext* getContext(lua_State* pLuaState);

private:
  lua_State* m_pLuaState;
  std::list<std::shared_ptr<renga_script::AbstractParameter>> m_params;

private:
  static std::map<lua_State*, RuntimeContext*> m_registry;
};
