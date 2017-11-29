#include <Parameter.h>

namespace renga_script
{
  // AbstractParameter
  AbstractParameter::AbstractParameter(const std::wstring & name)
    : m_name(name)
  {}

  AbstractParameter::AbstractParameter(const AbstractParameter & other)
    : m_name(other.m_name)
  {
  }

  AbstractParameter::~AbstractParameter()
  {}

  const std::wstring & AbstractParameter::name() const
  {
    return m_name;
  }  

  // MetricParameter
  MetricParameter::MetricParameter(const std::wstring & name, double defaultValue)
    : AbstractParameter(name)
    , m_value(defaultValue)
  {}

  MetricParameter::MetricParameter(const MetricParameter & other)
    : AbstractParameter(other)
    , m_value(other.m_value)
  {
  }
  
  MetricParameter::~MetricParameter()
  {}
  
  double MetricParameter::value() const
  {
    return m_value;
  }
  
  void MetricParameter::setValue(double value)
  {
    m_value = value;
  }
}