#pragma once
#include <RengaScript/Parameter.h>

namespace renga_script
{
  class IParameters
  {
  public:
    virtual bool setParameter(MetricParameter& parameter) = 0;
  };
}
