#pragma once
#include <RengaScript/ExecuteScript.h>

#include <map>
#include <memory>

struct lua_State;

namespace lua
{
  class ScriptRuntimeContext
  {
  public:
    ScriptRuntimeContext(lua_State* pLuaState, const renga_script::Object3DConstructionContext& context);
    ~ScriptRuntimeContext();

    renga_script::IParameters* getParameters() const;
    renga_script::IGeometryBuilder* getGeometryBuilder() const;

  public:
    static ScriptRuntimeContext* getContext(lua_State* pLuaState);

  private:
    lua_State* m_pLuaState;
    renga_script::Object3DConstructionContext m_object3DContext;
    std::unique_ptr<std::wstring> m_error; // using unique pointer as optional here

  private:
    static std::map<lua_State*, ScriptRuntimeContext*> m_registry;
  };
}