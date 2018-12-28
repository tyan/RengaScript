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
// Point3DWrapper
////////////////////////////////////////////////////////////////////////////
const std::string Point3DWrapper::s_type = "Point3D";

Point3DWrapper::Point3DWrapper(double x, double y, double z)
  : m_point(x, y, z)
{}

const std::string& Point3DWrapper::type() const
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
// Curve3DWrapper
////////////////////////////////////////////////////////////////////////////
const std::string Curve3DWrapper::s_type = "Curve3D";

Curve3DWrapper::Curve3DWrapper(renga_script::ICurve3D * pCurve)
  : m_pCurve(pCurve)
{
}

Curve3DWrapper::Curve3DWrapper(const Curve3DWrapper & other)
  : m_pCurve((other.m_pCurve) ? other.m_pCurve->copy() : nullptr)
{
}

Curve3DWrapper::Curve3DWrapper(Curve3DWrapper && other)
  : m_pCurve(std::move(other.m_pCurve))
{
  other.m_pCurve = nullptr;
}

Curve3DWrapper::~Curve3DWrapper()
{
  delete m_pCurve;
}

const std::string & Curve3DWrapper::type() const
{
  return s_type;
}

const renga_script::ICurve3D * Curve3DWrapper::curve() const
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

const renga_script::Point2DVector& Point2DVectorWrapper::getVector() const
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

////////////////////////////////////////////////////////////////////////////
// Curve3DVectorWrapper
////////////////////////////////////////////////////////////////////////////
Curve3DVectorWrapper::Curve3DVectorWrapper()
{}

Curve3DVectorWrapper::Curve3DVectorWrapper(const Curve3DVectorWrapper & other)
  : m_curves(other.m_curves)
{}

Curve3DVectorWrapper::Curve3DVectorWrapper(Curve3DVectorWrapper && other)
  : m_curves(std::move(other.m_curves))
{}

void Curve3DVectorWrapper::add(const Curve3DWrapper & curve)
{
  m_curves.push_back(curve);
}

const Curve3DWrapper & Curve3DVectorWrapper::get(size_t index) const
{
  return m_curves.at(index);
}

size_t Curve3DVectorWrapper::count() const
{
  return m_curves.size();
}

renga_script::ConstCurve3DVector Curve3DVectorWrapper::getCurves() const
{
  renga_script::ConstCurve3DVector result;
  for (auto& curve : m_curves)
    result.push_back(curve.curve());
  return result;
}


////////////////////////////////////////////////////////////////////////////
// LCSWrapper
////////////////////////////////////////////////////////////////////////////
const std::string LCSWrapper::s_type = "LCS";

LCSWrapper::LCSWrapper(renga_script::ILCS * pLCS)
  : m_pLCS(pLCS)
{
}

LCSWrapper::LCSWrapper(const LCSWrapper & other)
  : m_pLCS((other.m_pLCS) ? other.m_pLCS->copy() : nullptr)
{
}

LCSWrapper::LCSWrapper(LCSWrapper && other)
  : m_pLCS(std::move(other.m_pLCS))
{
  other.m_pLCS = nullptr;
}

LCSWrapper::~LCSWrapper()
{
  delete m_pLCS;
}

const std::string & LCSWrapper::type() const
{
  return s_type;
}

const renga_script::ILCS * LCSWrapper::lcs() const
{
  return m_pLCS;
}

////////////////////////////////////////////////////////////////////////////
// Curve2DWrapper
////////////////////////////////////////////////////////////////////////////
const std::string SolidWrapper::s_type = "Solid";

SolidWrapper::SolidWrapper(renga_script::ISolid * pSolid)
  : m_pSolid(pSolid)
{
}

SolidWrapper::SolidWrapper(const SolidWrapper & other)
  : m_pSolid((other.m_pSolid) ? other.m_pSolid->copy() : nullptr)
{
}

SolidWrapper::SolidWrapper(SolidWrapper && other)
  : m_pSolid(std::move(other.m_pSolid))
{
  other.m_pSolid = nullptr;
}

SolidWrapper::~SolidWrapper()
{
  delete m_pSolid;
}

const std::string & SolidWrapper::type() const
{
  return s_type;
}

SolidWrapper SolidWrapper::operator+(const SolidWrapper & other) const
{
  return SolidWrapper(m_pSolid->getUnionWith(other.m_pSolid));
}

SolidWrapper SolidWrapper::operator-(const SolidWrapper & other) const
{
  return SolidWrapper(m_pSolid->getDifferenceWith(other.m_pSolid));
}

SolidWrapper SolidWrapper::operator&(const SolidWrapper & other) const
{
  return SolidWrapper(m_pSolid->getMultisolidWith(other.m_pSolid));
}

const renga_script::ISolid * SolidWrapper::solid() const
{
  return m_pSolid;
}

renga_script::ISolid * SolidWrapper::solid()
{
  return m_pSolid;
}
