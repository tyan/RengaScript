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

  lua::registerMetricParameterType(m_pLuaState);
  lua::registerPoint2D(m_pLuaState);
  lua::registerCurve2DWrapper(m_pLuaState);
  lua::registerRectType(m_pLuaState);
  lua::registerLineSegmentType(m_pLuaState);
}

ScriptRuntimeContext::~ScriptRuntimeContext()
{
  m_registry.erase(m_pLuaState);
}

IParameters * ScriptRuntimeContext::getParameters() const
{
  return m_object3DContext.pParameters;
}

IGeometry2DBuilder * ScriptRuntimeContext::getGeometry2DBuilder() const
{
  return m_object3DContext.pGeometryBuilder2D;
}

ScriptRuntimeContext * ScriptRuntimeContext::getContext(lua_State * pLuaState)
{
  return m_registry.at(pLuaState);
}
