#pragma once
#include <string>
#include <memory>

struct lua_State;

namespace lua
{
  void registerMetricParameterType(lua_State* pLuaState);

  void registerRectType(lua_State* pLuaState);
}