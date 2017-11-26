#pragma once
#include <map>

struct lua_State;

class RuntimeContext
{
public:
  RuntimeContext();
  ~RuntimeContext();

  lua_State* getLua();

public:
  static RuntimeContext* getContext(lua_State* pLuaState);

private:
  lua_State* m_pLuaState;

private:
  static std::map<lua_State*, RuntimeContext*> m_registry;
};
