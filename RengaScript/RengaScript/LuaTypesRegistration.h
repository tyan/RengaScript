#pragma once
#include <string>
#include <memory>

struct lua_State;

namespace lua
{
  void registerParameterType(lua_State* pLuaState);
}