#include <Script.h>

#include <lua.hpp>

#include <LuaBridge.h>

#include <iostream>

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
      lua_State *L = luaL_newstate();   /* opens Lua */

      luaL_openlibs(L);             /* opens the basic library */

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
        if (0 != luaL_loadfile(L, ".\\TestData\\plate.rso"))
          throw "Cannot find file!\n";

        if (0 != lua_pcall(L, 0, 0, 0))
          throw "Cannot run file!\n";
      }
      catch (const char*  msg)
      {
        std::cout << msg;
        // TODO: error output
      }
      catch (...)
      {
        // TODO: error output
      }

      lua_close(L);
    }

  private:
    std::wstring m_path;
  };

  Script::Script(const std::wstring & path)
    : m_pImpl(new Impl(path))
  {}
}
