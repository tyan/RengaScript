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

    bool run(const std::wstring& luaScriptPath, renga_script::Object3DConstructionContext& context);

  private:
    void executeScript(const std::wstring& path);
    void loadLibraryFiles();

  private:
    lua_State* m_pLuaState;
  };
}
