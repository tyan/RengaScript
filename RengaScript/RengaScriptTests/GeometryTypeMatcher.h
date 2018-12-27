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

inline Matcher<const ICurve2D*> CurveIdEqConst(int expectedId) {
  return MakeMatcher(new StubIdEqMatcher<const ICurve2D, Curve2DStub>(expectedId));
}

inline Matcher<const ICurve3D*> Curve3DIdEqConst(int expectedId) {
  return MakeMatcher(new StubIdEqMatcher<const ICurve3D, Curve3DStub>(expectedId));
}

inline Matcher<ISolid*> SolidIdEq(int expectedId) {
  return MakeMatcher(new StubIdEqMatcher<ISolid, SolidStub>(expectedId));
}

inline Matcher<const ISolid*> SolidIdEqConst(int expectedId) {
  return MakeMatcher(new StubIdEqMatcher<const ISolid, SolidStub>(expectedId));
}

inline Matcher<const ILCS*> LCSIdEqConst(int expectedId) {
  return MakeMatcher(new StubIdEqMatcher<const ILCS, LCSStub>(expectedId));
}