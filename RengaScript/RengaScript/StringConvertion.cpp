#include "StringConvertion.h"

#include <codecvt>

std::wstring convertString(const std::string & str)
{
  typedef std::codecvt_utf8<wchar_t> convert_type;
  std::wstring_convert<convert_type, wchar_t> converter;
  return converter.from_bytes(str);
}
