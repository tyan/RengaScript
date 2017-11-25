#pragma once

#include "ApiDefines.h"

#include <string>

namespace renga_script
{
  class AbstractParameter
  {
  public:
    virtual ~AbstractParameter() = 0;
    virtual const std::wstring& name() const = 0;
  };

  class MetricParameter : public AbstractParameter
  {
  public:
    ~MetricParameter();
    
    // AbstractParameter
    const std::wstring& name() const override;

  private:
    MetricParameter(const std::wstring& name, double defaultValue);

  private:

  };
}
