#pragma once

#include "ApiDefines.h"

#include <string>

namespace renga_script
{
  // AbstractParameter
  class RENGA_SCRIPT_EXTERNAL AbstractParameter
  {
  public:
    virtual ~AbstractParameter();
    const std::wstring& name() const;
    
  protected:
    AbstractParameter(const std::wstring& name);
    AbstractParameter(const AbstractParameter& other);

  protected:
    // TODO: warning C4251 [tyan]
    std::wstring m_name;
  };

  // MetricParameter
  class RENGA_SCRIPT_EXTERNAL MetricParameter : public AbstractParameter
  {
  public:
    MetricParameter(const std::wstring& name, double defaultValue);
    MetricParameter(const MetricParameter& other);
   ~MetricParameter();

   double value() const;
   void setValue(double value);

  private:
    double m_value;
  };
}
