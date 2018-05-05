#pragma once

template<typename APIType, typename StubType>
class StubIdEqMatcher : public MatcherInterface<APIType*>
{
public:
  explicit StubIdEqMatcher(int expectedCurveId)
    : m_expectedId(expectedCurveId) {}

  virtual bool MatchAndExplain(APIType* pObject, MatchResultListener* listener) const
  {
    auto pStub = dynamic_cast<const StubType*>(pObject);
    assert(pStub);
    return pStub->id == m_expectedId;
  }

  virtual void DescribeTo(::std::ostream* os) const {
    *os << typeid(StubType).name() << " id is equal to " << m_expectedId;
  }

private:
  const int m_expectedId;
};

inline Matcher<const ICurve2D*> CurveIdEqConst(int expectedCurveId) {
  return MakeMatcher(new StubIdEqMatcher<const ICurve2D, Curve2DStub>(expectedCurveId));
}

inline Matcher<ISolid*> SolidIdEq(int expectedCurveId) {
  return MakeMatcher(new StubIdEqMatcher<ISolid, SolidStub>(expectedCurveId));
}

inline Matcher<const ILCS*> LCSIdEqConst(int expectedCurveId) {
  return MakeMatcher(new StubIdEqMatcher<const ILCS, LCSStub>(expectedCurveId));
}