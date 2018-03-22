#pragma once
#include <string>
#include <memory>

struct lua_State;

namespace lua
{
  void registerMetricParameterType(lua_State* pLuaState);
  
  void registerPoint2D(lua_State * pLuaState);
  void registerCurve2DWrapper(lua_State * pLuaState);
  void registerRectType(lua_State* pLuaState);
  void registerLineSegmentType(lua_State* pLuaState);
}