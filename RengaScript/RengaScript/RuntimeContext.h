#pragma once
#include <map>

struct lua_State;

class ScriptData;

namespace renga_script
{
  class AbstractParameter;
  class MetricParameter;
}

class RuntimeContext
{
public:
  RuntimeContext(lua_State* pLuaState, ScriptData& data);
  ~RuntimeContext();

  renga_script::MetricParameter* addMetricParameter(const std::wstring& name, double value);

public:
  static RuntimeContext* getContext(lua_State* pLuaState);

private:
  lua_State* m_pLuaState;
  ScriptData& m_data;

private:
  static std::map<lua_State*, RuntimeContext*> m_registry;
};
