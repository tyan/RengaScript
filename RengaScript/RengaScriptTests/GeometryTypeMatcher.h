#pragma once

class CurveIdEqMatcher : public MatcherInterface<const ICurve2D*> 
{
public:
  explicit CurveIdEqMatcher(int expectedCurveId)
    : m_expectedId(expectedCurveId) {}

  virtual bool MatchAndExplain(const ICurve2D* pCurve, MatchResultListener* listener) const 
  {
    auto pStub = dynamic_cast<const Curve2DStub*>(pCurve);
    assert(pStub);
    return pStub->id == m_expectedId;
  }

  virtual void DescribeTo(::std::ostream* os) const {
    *os << "Curve id is equal to " << m_expectedId;
  }

private:
  const int m_expectedId;
};

inline Matcher<const ICurve2D*> CurveIdEq(int expectedCurveId) {
  return MakeMatcher(new CurveIdEqMatcher(expectedCurveId));
}