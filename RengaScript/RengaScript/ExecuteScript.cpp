#include <RengaScript/ExecuteScript.h>

#include "LuaScriptRunner.h"
#include "PythonScriptRunner.h"


namespace renga_script
{
  RENGA_SCRIPT_EXTERNAL bool executeLuaScript(const std::wstring & path, Object3DConstructionContext & context)
  {
    lua::ScriptRunner luaRunner;
    return luaRunner.run(path, context);
  }

  RENGA_SCRIPT_EXTERNAL bool executePyScript(const std::wstring & path, Object3DConstructionContext & context)
  {
    py::ScriptRunner pythonRunner;
    return pythonRunner.run(path, context);
  }
}
