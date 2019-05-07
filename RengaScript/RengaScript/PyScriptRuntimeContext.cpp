#include "PyScriptRuntimeContext.h"
#include "RengaPyModule.h"

#include <frameobject.h>

using namespace renga_script;
using namespace py;
using namespace boost::python;

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_renga
extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initmymodule
extern "C" void INIT_MODULE();
#endif

ScriptRuntimeContext* ScriptRuntimeContext::m_pContext = nullptr;

ScriptRuntimeContext::ScriptRuntimeContext(const Object3DConstructionContext& context)
  : m_object3DContext(context)
{
  PyImport_AppendInittab((char*)"renga", INIT_MODULE);
  Py_Initialize();
  object main_module = import("__main__");
  dict main_namespace = extract<dict>(main_module.attr("__dict__"));
  object mymodule = import("renga");

  m_globals = main_namespace;
  m_locals = main_namespace;
  m_pContext = this;
}

ScriptRuntimeContext::~ScriptRuntimeContext()
{
  m_pContext = nullptr;
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

ScriptRuntimeContext * ScriptRuntimeContext::getContext()
{
  return m_pContext;
}

const boost::python::dict& ScriptRuntimeContext::getGlobals() const
{
  return m_globals;
}

const boost::python::dict& ScriptRuntimeContext::getLocals() const
{
  return m_locals;
}