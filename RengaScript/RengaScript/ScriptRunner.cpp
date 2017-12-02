#include <ScriptRunner.h>

#include "LuaScriptRunner.h"
#include "StateImpl.h"


namespace renga_script
{
  class ScriptRunner::Impl
  {
  public:
    Impl(const std::wstring & path)
      : m_path(path)
    {
    }

    bool run(ScriptData& data)
    {
      LuaScriptRunner luaRunner;
      return luaRunner.run(m_path, data);
    }

  private:
    std::wstring m_path;
  };

  ScriptRunner::ScriptRunner(const std::wstring & path)
    : m_pImpl(new Impl(path))
  {}

  bool ScriptRunner::run(State& state)
  {
    return m_pImpl->run(state.m_pImpl->m_data);
  }
}
