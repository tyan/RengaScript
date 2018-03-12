#include "Path.h"
#include "dllmain.h"

#include <experimental/filesystem>

static std::wstring s_dllDir;

const std::wstring & getDllDir()
{
  if (s_dllDir.empty())
  {
    constexpr size_t buffSize = 1024;
    wchar_t pBuff[buffSize];
    if (0 != GetModuleFileName(s_dllHModule, pBuff, buffSize))
    {
      std::experimental::filesystem::path path(pBuff);
      s_dllDir = path.parent_path();
    }
    else
    {
      throw std::wstring(L"Error while getting dll path.");
    }
  }
  return s_dllDir;
}
