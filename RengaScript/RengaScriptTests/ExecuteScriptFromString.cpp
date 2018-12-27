#include "stdafx.h"
#include "ExecuteScriptFromString.h"

#include <fstream>
#include <codecvt>

const std::wstring temporaryFilePath = L".\\tmp.lua";

class CScopedFileRemover
{
public:
  CScopedFileRemover(const std::wstring& filePath):
    m_filePath(filePath)
  {}

  ~CScopedFileRemover()
  {
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::remove(converter.to_bytes(m_filePath).c_str());
  }

private:
  const std::wstring& m_filePath;
};

bool executeScriptFromString(const std::wstring & script, renga_script::Object3DConstructionContext & context)
{
  CScopedFileRemover scopedFileRemover(temporaryFilePath);
  std::wofstream stream(temporaryFilePath);
  stream << script;
  stream.flush();
  return renga_script::executeScript(temporaryFilePath, context);
}
