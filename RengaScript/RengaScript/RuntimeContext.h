#pragma once
#include <map>
#include <memory>

struct lua_State;

namespace renga_script
{
  class AbstractParameter;
}

class RuntimeContext
{
public:
  RuntimeContext();
  ~RuntimeContext();

  lua_State* getLua();
  std::map<std::wstring, std::shared_ptr<renga_script::AbstractParameter>>& params();

public:
  static RuntimeContext* getContext(lua_State* pLuaState);

private:
  lua_State* m_pLuaState;
  std::map<std::wstring, std::shared_ptr<renga_script::AbstractParameter>> m_params;

private:
  static std::map<lua_State*, RuntimeContext*> m_registry;
};
