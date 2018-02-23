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

  RENGA_SCRIPT_EXTERNAL bool executeScript(const std::wstring& path, 
                                           const Object3DConstructionContext& context);
}
