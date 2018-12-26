#include <RengaScript/Parameter.h>

namespace renga_script
{
  // AbstractParameter
  AbstractParameter::AbstractParameter(const std::wstring & name, const std::wstring& category)
    : m_name(name)
    , m_category(category)
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

  const std::wstring & AbstractParameter::category() const
  {
    return m_category;
  }

  // MetricParameter
  MetricParameter::MetricParameter(const std::wstring & name, double defaultValue, const std::wstring& category)
    : AbstractParameter(name, category)
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