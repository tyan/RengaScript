#pragma once
#include <string>
#include <memory>

struct lua_State;

namespace lua
{
  void registerParametersTypes(lua_State* pLuaState);
  
  void registerGeometryTypes(lua_State * pLuaState);
}