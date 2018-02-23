#pragma once
#include <string>

struct lua_State;

namespace renga_script
{
	class Object3DConstructionContext;
}

namespace lua
{
  class ScriptRunner
  {
  public:
    ScriptRunner();
    ~ScriptRunner();

    bool run(const std::wstring& luaScriptPath, const renga_script::Object3DConstructionContext& context);

  private:
    lua_State* m_pLuaState;
  };
}
