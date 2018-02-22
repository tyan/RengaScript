#pragma once
#include <string>

struct lua_State;

namespace renga_script
{
	class Object3DConstructionContext;
}

class LuaScriptRunner
{
public:
  LuaScriptRunner();
  ~LuaScriptRunner();

  bool run(const std::wstring& luaScriptPath, const renga_script::Object3DConstructionContext& context);

private:
  lua_State* m_pLuaState;
};
