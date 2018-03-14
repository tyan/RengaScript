#include "Geometry2DTypeWrapper.h"

#include <utility>

using namespace lua;

Curve2DWrapper::Curve2DWrapper(renga_script::ICurve2D * pCurve)
  : m_pCurve(pCurve)
{
}

Curve2DWrapper::Curve2DWrapper(const Curve2DWrapper & other)
  : m_pCurve(other.m_pCurve->copy())
{
}

lua::Curve2DWrapper::Curve2DWrapper(Curve2DWrapper && other)
  : m_pCurve(std::move(other.m_pCurve))
{
  other.m_pCurve = nullptr;
}

Curve2DWrapper::~Curve2DWrapper()
{
  delete m_pCurve;
}
