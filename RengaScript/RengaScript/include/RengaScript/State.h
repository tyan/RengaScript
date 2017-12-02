#pragma once
#include "ApiDefines.h"
#include "Parameter.h"

namespace renga_script
{
  class RENGA_SCRIPT_EXTERNAL State
  {
  public:
    State();
    ~State();
    
    size_t getParametersCount() const;
    const AbstractParameter* getParameter(size_t i) const;

  private:
    friend class ScriptRunner;
    class Impl;
    Impl* m_pImpl;
  };
}
