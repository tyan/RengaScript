#pragma once
#include "ScriptData.h"
#include "State.h"

namespace renga_script
{
  class State::Impl
  {
  public:
    ScriptData m_data;
  };
}
