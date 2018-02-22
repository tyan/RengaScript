#pragma once
#include <RengaScript/ScriptRunner.h>

#include <map>

struct lua_State;

namespace renga_script
{
  class RuntimeContext
  {
  public:
    RuntimeContext(lua_State* pLuaState, const Object3DConstructionContext& context);
    ~RuntimeContext();

    IParametersService* getParameters() const;
    IGeometryBuilder* getGeometryBuilder() const;

  public:
    static RuntimeContext* getContext(lua_State* pLuaState);

  private:
    lua_State* m_pLuaState;
    Object3DConstructionContext m_object3DContext;

  private:
    static std::map<lua_State*, RuntimeContext*> m_registry;
  };
}