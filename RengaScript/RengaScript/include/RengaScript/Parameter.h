#pragma once

#include <RengaScript/ApiDefines.h>
#include <string>

#pragma warning( push )
#pragma warning( disable : 4251 )

namespace renga_script
{
  // AbstractParameter
  class RENGA_SCRIPT_EXTERNAL AbstractParameter
  {
  public:
    virtual ~AbstractParameter();
    const std::wstring& name() const;
    const std::wstring& category() const;
    virtual bool isEqual(const AbstractParameter* pOther) const;
    virtual AbstractParameter* copy() const = 0;

  protected:
    AbstractParameter(const std::wstring & name, const std::wstring& category);
    AbstractParameter(const AbstractParameter& other);

  protected:
    // TODO: warning C4251 [tyan]
    std::wstring m_name;
    std::wstring m_category;
  };

  // MetricParameter
  class RENGA_SCRIPT_EXTERNAL MetricParameter : public AbstractParameter
  {
  public:
    MetricParameter(const std::wstring & name, double defaultValue, const std::wstring& category = L"");
    MetricParameter(const MetricParameter& other);
   ~MetricParameter();
   
   // AbstractParameter
   bool isEqual(const AbstractParameter* pOther) const override;
   AbstractParameter* copy() const override;

   // own
   double value() const;
   void setValue(double value);

  private:
    double m_value;
  };
}

#pragma warning (pop)