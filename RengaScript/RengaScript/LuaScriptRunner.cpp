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

bool ScriptRunner::run(const std::wstring& luaScriptPath, renga_script::Object3DConstructionContext& context)
{
  try
  {
    ScriptRuntimeContext runtimeContext(m_pLuaState, context);
    loadLibraryFiles();
    executeScript(luaScriptPath);
  }
  catch (const std::wstring& error)
  {
    context.error = error;
    return false;
  }
  catch (...)
  {
    context.error = L"Unknown error";
    return false;
  }
  return true;
}

void ScriptRunner::executeScript(const std::wstring & path)
{
  if (0 != luaL_loadfile(m_pLuaState, convertString(path).c_str()))
  {
    const char* errorMessage = lua_tostring(m_pLuaState, -1);
    throw std::wstring(L"Error while loading script: ") + path + std::wstring(L", Error message: ") + convertString(errorMessage);
  }

  if (0 != lua_pcall(m_pLuaState, 0, 0, 0))
  {
    const char* errorMessage = lua_tostring(m_pLuaState, -1);
    throw std::wstring(L"Error while executing script: ") + path + std::wstring(L", Error message: ") + convertString(errorMessage);
  }
}

void lua::ScriptRunner::loadLibraryFiles()
{
}
