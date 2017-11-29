#pragma once
#include <string>
#include <memory>

struct lua_State;

namespace renga_script
{
  class MetricParameter;
}

class MetricParameterWrapper
{
public:
  static void RegisterType(lua_State* pLuaState);

public:
  MetricParameterWrapper(char const* name, double defaultValue, lua_State* pLuaState);
  MetricParameterWrapper(const MetricParameterWrapper& other) = delete;

private:
  renga_script::MetricParameter* m_pImp;
};