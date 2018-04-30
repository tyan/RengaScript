#pragma once

#include <RengaScript/GeometryTypes.h>

namespace lua
{
  class Point2DWrapper
  {
  public:
    Point2DWrapper() = default;
    Point2DWrapper(const Point2DWrapper& other) = default;
    Point2DWrapper(Point2DWrapper&& other) = default;
    ~Point2DWrapper() = default;

    Point2DWrapper(double x, double y);
    const std::string& type() const;

  public:
    // TODO: extract interface or friend accessor
    // internal access
    renga_script::Point2D m_point;

  private:
    static const std::string s_type;
  };

  class Point3DWrapper
  {
  public:
    Point3DWrapper() = default;
    Point3DWrapper(const Point3DWrapper& other) = default;
    Point3DWrapper(Point3DWrapper&& other) = default;
    ~Point3DWrapper() = default;

    Point3DWrapper(double x, double y, double z);
    const std::string& type() const;

  public:
    // TODO: extract interface or friend accessor
    // internal access
    renga_script::Point3D m_point;

  private:
    static const std::string s_type;
  };

  class Curve2DWrapper
  {
  public:
    Curve2DWrapper(renga_script::ICurve2D* pCurve);
    Curve2DWrapper(const Curve2DWrapper& other);
    Curve2DWrapper(Curve2DWrapper&& other);
    ~Curve2DWrapper();
    const std::string& type() const;
    Curve2DWrapper operator+(const Curve2DWrapper& other) const;
    
    // TODO: extract interface or friend accessor
    // internal access
    const renga_script::ICurve2D* curve() const;

  private:
    renga_script::ICurve2D* m_pCurve;
    static const std::string s_type;
  };
  
  class CurveVectorWrapper
  {
  public:
    CurveVectorWrapper();
    CurveVectorWrapper(const CurveVectorWrapper& other);
    CurveVectorWrapper(CurveVectorWrapper&& other);
    void add(const Curve2DWrapper& curve);
    const Curve2DWrapper& get(size_t index) const;
    size_t count() const;

    // TODO: extract interface or friend accessor
    // internal access
    renga_script::ConstCurveVector getCurves() const;

  private:
    std::vector<Curve2DWrapper> m_curves;
  };

  class Point2DVectorWrapper
  {
  public:
    Point2DVectorWrapper();
    Point2DVectorWrapper(const Point2DVectorWrapper& other);
    Point2DVectorWrapper(Point2DVectorWrapper&& other);
    ~Point2DVectorWrapper();

    void add(const Point2DWrapper& point);
    Point2DWrapper get(size_t index) const;
    size_t count() const;

    // TODO: extract interface or friend accessor
    // internal access
    const renga_script::PointVector& getVector() const;

  private:
    renga_script::PointVector m_vector;
  };

  class LCSWrapper
  {
  public:
    LCSWrapper(renga_script::ILCS* pCurve);
    LCSWrapper(const LCSWrapper& other);
    LCSWrapper(LCSWrapper&& other);
    ~LCSWrapper();
    const std::string& type() const;

    // TODO: extract interface or friend accessor
    // internal access
    const renga_script::ILCS* lcs() const;

  private:
    renga_script::ILCS* m_pLCS;
    static const std::string s_type;
  };

  class SolidWrapper
  {
  public:
    SolidWrapper(renga_script::ISolid* pSolid);
    SolidWrapper(const SolidWrapper& other);
    SolidWrapper(SolidWrapper&& other);
    ~SolidWrapper();
    const std::string& type() const;
    SolidWrapper operator+(const SolidWrapper& other) const;

    // TODO: extract interface or friend accessor
    // internal access
    const renga_script::ISolid* solid() const;

  private:
    renga_script::ISolid* m_pSolid;
    static const std::string s_type;
  };
}