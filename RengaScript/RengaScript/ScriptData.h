#pragma once
#include "Parameter.h"

#include <memory>
#include <vector>

typedef std::shared_ptr<renga_script::AbstractParameter> AbstractParameterPtr;

class ScriptData
{
public:
  std::vector<AbstractParameterPtr> m_parameters;
};
