#include "LuaScriptRunner.h"
#include "StringConvertion.h"
#include "LuaScriptRuntimeContext.h"

#include <lua.hpp>

using namespace renga_script;
using namespace lua;

ScriptRunner::ScriptRunner()
{
  m_pLuaState = luaL_newstate();   /* opens Lua */
  luaL_openlibs(m_pLuaState);      /* opens the basic library */
}

ScriptRunner::~ScriptRunner()
{
  lua_close(m_pLuaState);
}

bool ScriptRunner::run(const std::wstring& luaScriptPath, const renga_script::Object3DConstructionContext& context)
{
  try
  {
    ScriptRuntimeContext runtimeContext(m_pLuaState, context);

    if (0 != luaL_loadfile(m_pLuaState, convertString(luaScriptPath).c_str()))
      throw L"Cannot find file!";

    if (0 != lua_pcall(m_pLuaState, 0, 0, 0))
      throw L"Cannot run file!";
  }
  catch (const std::wstring&)
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
