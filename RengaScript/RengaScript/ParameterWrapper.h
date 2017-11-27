#pragma once
#include <string>
#include <memory>

#include <Parameter.h>

struct lua_State;

class MetricParameterWrapper
{
public:
  static void RegisterType(lua_State* pLuaState);

public:
  MetricParameterWrapper(char const* name, double defaultValue, lua_State* pLuaState);
  MetricParameterWrapper(const MetricParameterWrapper& other) = delete;

private:
  std::shared_ptr<renga_script::MetricParameter> m_parameter;
};