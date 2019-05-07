#include "RengaPyModule.h"
#include "PyScriptRuntimeContext.h"

#include <boost/python.hpp>

#include <RengaScript/IParameters.h>

using namespace boost::python;
using namespace py; // local namespace

renga_script::MetricParameter* Parameters::createMetric(std::wstring name, double defaultValue)
{
  auto pParametersBackend = ScriptRuntimeContext::getContext()->getParameters();
  auto parameter = renga_script::MetricParameter(name, defaultValue);
  auto parameterWasSet = pParametersBackend->setParameter(parameter);
  if (parameterWasSet == false)
    throw std::wstring(L"Failed to set parameter: ") + name; // TODO: message duplicate
  return new renga_script::MetricParameter(name, defaultValue);
}

BOOST_PYTHON_MODULE(renga)
{
  class_<renga_script::MetricParameter>("MetricParameter", no_init)
    ;

  class_<Parameters>("params")
    .def("create_metric", &Parameters::createMetric, return_value_policy<manage_new_object>())
    ;
}