#pragma once
#include <RengaScript/ApiDefines.h>

#include <string>

namespace renga_script
{
  class IParameters;
  class IGeometry2DBuilder;
  class IGeometry3DBuilder;
  class IObject3DDefinition;
}

namespace renga_script
{
  class Object3DConstructionContext
  {
  public:
    IParameters* pParameters = nullptr;
    IGeometry2DBuilder* pGeometryBuilder2D = nullptr;
    IGeometry3DBuilder* pGeometryBuilder3D = nullptr;
    IObject3DDefinition* pObject3DDefinition = nullptr;
  };

  RENGA_SCRIPT_EXTERNAL bool executeScript(const std::wstring& path, 
                                           const Object3DConstructionContext& context);
}
