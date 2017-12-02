#include "State.h"
#include "ScriptData.h"
#include "StateImpl.h"

namespace renga_script
{
  State::State()
    : m_pImpl(new Impl())
  {
  }

  State::~State()
  {
    delete m_pImpl;
  }

  size_t State::getParametersCount() const
  {
    return m_pImpl->m_data.m_parameters.size();
  }

  const AbstractParameter * State::getParameter(size_t i) const
  {
    return m_pImpl->m_data.m_parameters[i].get();
  }
}
