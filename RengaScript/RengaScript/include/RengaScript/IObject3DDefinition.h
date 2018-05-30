#pragma once
#include <RengaScript/GeometryTypes.h>

namespace renga_script
{
  class IObject3DDefinition
  {
  public:
    virtual void setSolidRepresentation(const ISolid* pSolid) = 0;
  };
}
