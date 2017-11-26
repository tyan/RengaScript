#include "RuntimeContext.h"

#include <lua.hpp>

std::map<lua_State*, RuntimeContext*> RuntimeContext::m_registry;

RuntimeContext::RuntimeContext()
  : m_pLuaState(nullptr)
{
  m_pLuaState = luaL_newstate();   /* opens Lua */
  luaL_openlibs(m_pLuaState);      /* opens the basic library */

  m_registry.insert(std::make_pair(m_pLuaState, this));
}

RuntimeContext::~RuntimeContext()
{
  m_registry.erase(m_pLuaState);

  lua_close(m_pLuaState);
}

lua_State * RuntimeContext::getLua()
{
  return m_pLuaState;
}

RuntimeContext * RuntimeContext::getContext(lua_State * pLuaState)
{
  return m_registry.at(pLuaState);
}
