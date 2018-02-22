#include "LuaScriptRunner.h"
#include "StringConvertion.h"
#include "RuntimeContext.h"

#include <lua.hpp>

using namespace renga_script;

LuaScriptRunner::LuaScriptRunner()
{
  m_pLuaState = luaL_newstate();   /* opens Lua */
  luaL_openlibs(m_pLuaState);      /* opens the basic library */
}

LuaScriptRunner::~LuaScriptRunner()
{
  lua_close(m_pLuaState);
}

bool LuaScriptRunner::run(const std::wstring& luaScriptPath, const renga_script::Object3DConstructionContext& context)
{
  RuntimeContext runtimeContext(m_pLuaState, context);
  try
  {
    if (0 != luaL_loadfile(m_pLuaState, convertString(luaScriptPath).c_str()))
      throw "Cannot find file!\n";

    if (0 != lua_pcall(m_pLuaState, 0, 0, 0))
      throw "Cannot run file!\n";
  }
  catch (const char*)
  {
    // TODO: report error [tyan]
    return false;
  }
  catch (...)
  {
    // TODO: report error [tyan]
    return false;
  }
  return true;
}
