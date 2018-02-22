#pragma once
#include <RengaScript/ApiDefines.h>

#include <string>

namespace renga_script
{
  class IParametersService;
  class IGeometryBuilder;
  class IObject3DDefinition;
}

namespace renga_script
{
  class Object3DConstructionContext
  {
  public:
    IParametersService* pParameters = nullptr;
    IGeometryBuilder* pGeometryBuilder = nullptr;
    IObject3DDefinition* pObject3DDefinition = nullptr;
  };

  class RENGA_SCRIPT_EXTERNAL ScriptRunner
  {
  public:
    ScriptRunner(const std::wstring& path);
    bool run(const Object3DConstructionContext& context);

  private:
    ScriptRunner() = delete;

  private:
    class Impl;
    Impl* m_pImpl;
  };
}
