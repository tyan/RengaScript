#include <RengaScript/ExecuteScript.h>

#include "LuaScriptRunner.h"


namespace renga_script
{
  RENGA_SCRIPT_EXTERNAL bool executeScript(const std::wstring & path, Object3DConstructionContext & context)
  {
    lua::ScriptRunner luaRunner;
    return luaRunner.run(path, context);
  }
}
