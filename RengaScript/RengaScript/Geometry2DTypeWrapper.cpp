#include "Geometry2DTypeWrapper.h"

#include <utility>

using namespace lua;

////////////////////////////////////////////////////////////////////////////
// Curve2DWrapper
////////////////////////////////////////////////////////////////////////////
Curve2DWrapper::Curve2DWrapper(renga_script::ICurve2D * pCurve)
  : m_pCurve(pCurve)
{
}

Curve2DWrapper::Curve2DWrapper(const Curve2DWrapper & other)
  : m_pCurve((other.m_pCurve) ? other.m_pCurve->copy() : nullptr)
{
}

Curve2DWrapper::Curve2DWrapper(Curve2DWrapper && other)
  : m_pCurve(std::move(other.m_pCurve))
{
  other.m_pCurve = nullptr;
}

Curve2DWrapper::~Curve2DWrapper()
{
  delete m_pCurve;
}

////////////////////////////////////////////////////////////////////////////
// Point2DVectorWrapper
////////////////////////////////////////////////////////////////////////////
Point2DVectorWrapper::Point2DVectorWrapper()
{}

Point2DVectorWrapper::Point2DVectorWrapper(const Point2DVectorWrapper & other)
  : m_vector(other.m_vector)
{}

Point2DVectorWrapper::Point2DVectorWrapper(Point2DVectorWrapper && other)
  : m_vector(std::move(other.m_vector))
{}

Point2DVectorWrapper::~Point2DVectorWrapper()
{}

void Point2DVectorWrapper::add(renga_script::Point2D point)
{
  m_vector.push_back(point);
}

const renga_script::Point2D & Point2DVectorWrapper::get(size_t index) const
{
  return m_vector.at(index);
}

size_t Point2DVectorWrapper::count() const
{
  return m_vector.size();
}

const renga_script::PointVector& Point2DVectorWrapper::getVector() const
{
  return m_vector;
}
