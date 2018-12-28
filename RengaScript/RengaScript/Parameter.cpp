#include <RengaScript/Parameter.h>

#include <math.h>

namespace renga_script
{
  // AbstractParameter
  AbstractParameter::AbstractParameter(const std::wstring & name, const std::wstring& category)
    : m_name(name)
    , m_category(category)
  {}

  AbstractParameter::AbstractParameter(const AbstractParameter & other)
    : m_name(other.m_name)
  {}

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

  bool AbstractParameter::isEqual(const AbstractParameter* pOther) const
  {
    return m_name == pOther->m_name && m_category == pOther->m_category;
  }

  // MetricParameter
  MetricParameter::MetricParameter(const std::wstring & name, double defaultValue, const std::wstring& category)
    : AbstractParameter(name, category)
    , m_value(defaultValue)
  {}

  MetricParameter::MetricParameter(const MetricParameter & other)
    : AbstractParameter(other)
    , m_value(other.m_value)
  {}
  
  MetricParameter::~MetricParameter()
  {}

  bool MetricParameter::isEqual(const AbstractParameter* pOther) const
  {
    if (false == AbstractParameter::isEqual(pOther))
      return false;

    auto pOtherMetricParameter = dynamic_cast<const MetricParameter*>(pOther);
    return pOtherMetricParameter && fabs(pOtherMetricParameter->m_value - m_value) < 0.001;
  }

  AbstractParameter * MetricParameter::copy() const
  {
    return nullptr;
  }
  
  double MetricParameter::value() const
  {
    return m_value;
  }
  
  void MetricParameter::setValue(double value)
  {
    m_value = value;
  }
}