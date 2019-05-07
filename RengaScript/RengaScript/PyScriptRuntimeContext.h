#pragma once
#include <RengaScript/ExecuteScript.h>

#include <boost/python.hpp>

namespace py
{
  class ScriptRuntimeContext
  {
  public:
    ScriptRuntimeContext(const renga_script::Object3DConstructionContext& context);
    ~ScriptRuntimeContext();

    renga_script::IParameters* getParameters() const;
    renga_script::IGeometryBuilder* getGeometryBuilder() const;
    renga_script::IObject3DDefinition* getObject3DDefinition() const;
    const boost::python::dict& getGlobals() const;
    const boost::python::dict& getLocals() const;

  public:
    static ScriptRuntimeContext* getContext();

  private:
    boost::python::dict m_globals;
    boost::python::dict m_locals;
    const renga_script::Object3DConstructionContext& m_object3DContext;

  private:
    static ScriptRuntimeContext* m_pContext;
  };
}