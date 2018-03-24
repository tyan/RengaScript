#pragma once
#include <string>
#include <memory>

struct lua_State;

namespace lua
{
  void registerParametersTypes(lua_State* pLuaState);
  
  void registerGeometry2DTypes(lua_State * pLuaState);
}