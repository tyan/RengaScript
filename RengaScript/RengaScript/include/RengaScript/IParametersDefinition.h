#pragma once
#include "Parameters.h"

namespace renga_script
{
  class IParametersDefinition
  {
  public:
    virtual bool setParameter(MetricParameter& parameter) = 0;
  };
}
