#include "PythonScriptRunner.h"
#include "StringConvertion.h"
#include "PyScriptRuntimeContext.h"

#include <RengaScript/ExecuteScript.h>

#include <boost/python.hpp>


using namespace py;

std::wstring fetchPythonErrorMessage()
{
  PyObject *pType, *pValue, *pTraceback;
  PyErr_Fetch(&pType, &pValue, &pTraceback);

  boost::python::handle<> hType(pType);
  boost::python::object extype(hType);
  boost::python::handle<> hTraceback(pTraceback);
  boost::python::object traceback(hTraceback);

  auto result = convertString(boost::python::extract<std::string>(pValue));
  PyErr_Clear();
  return result;
}

bool ScriptRunner::run(const std::wstring& path, renga_script::Object3DConstructionContext& context)
{
  try
  {
    ScriptRuntimeContext runtimeContext(context);

    boost::python::exec_file(
      convertString(path).c_str(),
      runtimeContext.getGlobals(),
      runtimeContext.getLocals());
    return true;
  }
  catch (boost::python::error_already_set& /*e*/)
  {
    context.error = fetchPythonErrorMessage();
    return false;
  }
  catch (const std::wstring& error)
  {
    context.error = error;
    return false;
  }
  catch (...)
  {
    context.error = L"Unknown error";
    return false;
  }
}