#include <Script.h>

#include <lua.hpp>

#include <LuaBridge.h>

#include "RuntimeContext.h"

namespace renga_script
{
  //void CreateId(Script* pScript, int id)
  //{
  //  /*if(pScript)
  //    return id;
  //  return 0;*/
  //}

  //class Parameter
  //{
  //public:
  //  Parameter(char const* pName, double defaultValue, lua_State *L)
  //    : m_name(pName)
  //    , m_value(defaultValue)
  //  {}

  //  const char* name() const
  //  {
  //    return m_name.c_str();
  //  }

  //private:
  //  const std::string m_name;
  //  double m_value;
  //};

  //Parameter MetricParameter(char const* pName, double defaultValue, lua_State *L)
  //{
  //  return Parameter(pName, defaultValue, nullptr);
  //}

  class Script::Impl
  {
  public:
    Impl(const std::wstring & path)
      : m_path(path)
    {
      RuntimeContext context;

      //luabridge::getGlobalNamespace(L)
      //  //.beginNamespace("renga_script")
      //  .beginClass <Parameter>("MetricParameterObj")
      //  .addFunction("name", &Parameter::name)
      //  .addConstructor<void(*) (char const*, double, lua_State *)>()
      //  .endClass()
      //  //.endNamespace()
      //  ;

      //luabridge::getGlobalNamespace(L)
      //  .addFunction("MetricParameter", &MetricParameter);

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
