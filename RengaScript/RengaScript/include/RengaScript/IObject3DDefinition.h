#pragma once
#include "Parameter.h"

namespace renga_script
{
  class IObject3DDefinition
  {
  public:
    virtual void set3DGeometry() = 0;
  };
}
