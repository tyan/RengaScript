#pragma once
#include <RengaScript/Parameter.h>


namespace py
{
  class Parameters 
  {
  public:
    static renga_script::MetricParameter* createMetric(std::wstring name, double defaultValue);
  };
}