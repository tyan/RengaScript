#include "GeometryTypeWrapper.h"

#include <utility>

using namespace lua;


////////////////////////////////////////////////////////////////////////////
// Point2DWrapper
////////////////////////////////////////////////////////////////////////////
const std::string Point2DWrapper::s_type = "Point";

Point2DWrapper::Point2DWrapper(double x, double y)
  : m_point(x, y)
{}

const std::string& Point2DWrapper::type() const
{
  return s_type;
}

////////////////////////////////////////////////////////////////////////////
// Curve2DWrapper
////////////////////////////////////////////////////////////////////////////
const std::string Curve2DWrapper::s_type = "Curve";

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

const std::string & Curve2DWrapper::type() const
{
  return s_type;
}

Curve2DWrapper Curve2DWrapper::operator+(const Curve2DWrapper & other) const
{
  return Curve2DWrapper(m_pCurve->getUnionWith(other.m_pCurve));
}

const renga_script::ICurve2D * Curve2DWrapper::curve() const
{
  return m_pCurve;
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

void Point2DVectorWrapper::add(const Point2DWrapper& pointWrapper)
{
  m_vector.push_back(pointWrapper.m_point);
}

Point2DWrapper Point2DVectorWrapper::get(size_t index) const
{
  const renga_script::Point2D& point = m_vector.at(index);
  return Point2DWrapper(point.x, point.y);
}

size_t Point2DVectorWrapper::count() const
{
  return m_vector.size();
}

const renga_script::PointVector& Point2DVectorWrapper::getVector() const
{
  return m_vector;
}


////////////////////////////////////////////////////////////////////////////
// Curve2DVectorWrapper
////////////////////////////////////////////////////////////////////////////
CurveVectorWrapper::CurveVectorWrapper()
{}

CurveVectorWrapper::CurveVectorWrapper(const CurveVectorWrapper & other)
  : m_curves(other.m_curves)
{}

CurveVectorWrapper::CurveVectorWrapper(CurveVectorWrapper && other)
  : m_curves(std::move(other.m_curves))
{}

void CurveVectorWrapper::add(const Curve2DWrapper & curve)
{
  m_curves.push_back(curve);
}

const Curve2DWrapper & CurveVectorWrapper::get(size_t index) const
{
  return m_curves.at(index);
}

size_t CurveVectorWrapper::count() const
{
  return m_curves.size();
}

renga_script::ConstCurveVector CurveVectorWrapper::getCurves() const
{
  renga_script::ConstCurveVector result;
  for (auto& curve : m_curves)
    result.push_back(curve.curve());
  return result;
}
