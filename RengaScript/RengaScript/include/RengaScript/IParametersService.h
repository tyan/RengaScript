#pragma once
#include <RengaScript/Parameter.h>

namespace renga_script
{
  class IParametersService
  {
  public:
    virtual bool setParameter(MetricParameter& parameter) = 0;
  };
}
