#include <Script.h>

#include <lua.hpp>

#include <LuaBridge.h>

#include "RuntimeContext.h"

namespace renga_script
{
  class Script::Impl
  {
  public:
    Impl(const std::wstring & path)
      : m_path(path)
    {
      RuntimeContext context;

      try
      {
        if (0 != luaL_loadfile(context.getLua(), ".\\TestData\\plate.rso"))
          throw "Cannot find file!\n";

        if (0 != lua_pcall(context.getLua(), 0, 0, 0))
          throw "Cannot run file!\n";
      }
      catch (const char*)
      {
        // TODO: error output
      }
      catch (...)
      {
        // TODO: error output
      }
    }

  private:
    std::wstring m_path;
  };

  Script::Script(const std::wstring & path)
    : m_pImpl(new Impl(path))
  {}
}
