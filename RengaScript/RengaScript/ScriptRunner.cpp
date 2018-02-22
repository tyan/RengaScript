#include <RengaScript/ScriptRunner.h>

#include "LuaScriptRunner.h"


namespace renga_script
{
  class ScriptRunner::Impl
  {
  public:
    Impl(const std::wstring & path)
      : m_path(path)
    {
    }

    bool run(Object3DConstructionContext context)
    {
      LuaScriptRunner luaRunner;
      return luaRunner.run(m_path, context);
    }

  private:
    std::wstring m_path;
  };

  ScriptRunner::ScriptRunner(const std::wstring & path)
    : m_pImpl(new Impl(path))
  {}

  bool ScriptRunner::run(const Object3DConstructionContext& context)
  {
    return m_pImpl->run(context);
  }
}
