#pragma once
#include <RengaScript/ApiDefines.h>

#include <string>

namespace renga_script
{
  class IParameters;
  class IGeometryBuilder;
  class IObject3DDefinition;
}

namespace renga_script
{
  class Object3DConstructionContext
  {
  public:
    IParameters* pParameters = nullptr;
    IGeometryBuilder* pGeometryBuilder = nullptr;
    IObject3DDefinition* pObject3DDefinition = nullptr;
    std::wstring error;
  };

  RENGA_SCRIPT_EXTERNAL bool executeScript(const std::wstring& path, 
                                           Object3DConstructionContext& context);
}
