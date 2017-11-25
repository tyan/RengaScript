#pragma once
#include "ApiDefines.h"

#include <string>

namespace renga_script
{
  class RENGA_SCRIPT_EXTERNAL Script
  {
  public:
    Script(const std::wstring& path);

  private:
    Script() = delete;

  private:
    class Impl;
    Impl* m_pImpl;
  };
}
