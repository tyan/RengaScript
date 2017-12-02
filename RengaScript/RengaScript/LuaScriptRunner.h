#pragma once
#include <string>

struct lua_State;

class ScriptData;

class LuaScriptRunner
{
public:
  LuaScriptRunner();
  ~LuaScriptRunner();

  bool run(const std::wstring& luaScriptPath, ScriptData& data);

private:
  lua_State* m_pLuaState;
};
