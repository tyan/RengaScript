#pragma once
#include <RengaScript/IParameters.h>

class ParametersMock : public IParameters
{
public:
  MOCK_METHOD1(setParameter, bool(MetricParameter&));
};

typedef NiceMock<ParametersMock> ParametersNice;
typedef StrictMock<ParametersMock> ParametersStrict;