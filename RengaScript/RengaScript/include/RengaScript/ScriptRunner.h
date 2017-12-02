#pragma once
#include "ApiDefines.h"
#include "State.h"

#include <string>

namespace renga_script
{
  class RENGA_SCRIPT_EXTERNAL ScriptRunner
  {
  public:
    ScriptRunner(const std::wstring& path);
    bool run(State& state);

  private:
    ScriptRunner() = delete;

  private:
    class Impl;
    Impl* m_pImpl;
  };
}
