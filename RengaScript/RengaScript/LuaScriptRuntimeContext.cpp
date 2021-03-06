#include "LuaScriptRuntimeContext.h"
#include <RengaScript/Parameter.h>

#include "LuaTypesRegistration.h"

#include <assert.h>

using namespace renga_script;
using namespace lua;

std::map<lua_State*, ScriptRuntimeContext*> ScriptRuntimeContext::m_registry;

ScriptRuntimeContext::ScriptRuntimeContext(lua_State* pLuaState, const Object3DConstructionContext& context)
  : m_pLuaState(pLuaState)
  , m_object3DContext(context)
{
  assert(m_pLuaState != nullptr);
  m_registry.insert(std::make_pair(m_pLuaState, this));

  lua::registerParametersTypes(m_pLuaState);
  lua::registerGeometryTypes(m_pLuaState);
  lua::registerObject3DTypes(m_pLuaState);
}

ScriptRuntimeContext::~ScriptRuntimeContext()
{
  m_registry.erase(m_pLuaState);
}

IParameters * ScriptRuntimeContext::getParameters() const
{
  return m_object3DContext.pParameters;
}

IGeometryBuilder * ScriptRuntimeContext::getGeometryBuilder() const
{
  return m_object3DContext.pGeometryBuilder;
}

renga_script::IObject3DDefinition * ScriptRuntimeContext::getObject3DDefinition() const
{
  return m_object3DContext.pObject3DDefinition;
}

ScriptRuntimeContext * ScriptRuntimeContext::getContext(lua_State * pLuaState)
{
  return m_registry.at(pLuaState);
}
