#include <ScriptRunner.h>

#include "LuaScriptRunner.h"
#include "ScriptData.h"

namespace renga_script
{
  class ScriptRunner::Impl
  {
  public:
    Impl(const std::wstring & path)
      : m_path(path)
    {
    }

    bool run()
    {
      LuaScriptRunner luaRunner;
      return luaRunner.run(m_path, m_data);
    }

  private:
    std::wstring m_path;
    ScriptData m_data;
  };

  ScriptRunner::ScriptRunner(const std::wstring & path)
    : m_pImpl(new Impl(path))
  {}

  bool ScriptRunner::run()
  {
    return m_pImpl->run();
  }
}
