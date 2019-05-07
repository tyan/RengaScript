#pragma once
#include <string>

namespace renga_script
{
  class Object3DConstructionContext;
}

namespace py
{
  class ScriptRunner
  {
  public:
    ScriptRunner() = default;
    ~ScriptRunner() = default;

    bool run(const std::wstring& pyScriptPath, renga_script::Object3DConstructionContext& context);
  };
}
