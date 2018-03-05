#pragma once
#include <RengaScript/IParameters.h>

class ParametersMock : public renga_script::IParameters
{
public:
  MOCK_METHOD1(setParameter, bool(renga_script::MetricParameter&));
};

typedef NiceMock<ParametersMock> ParametersNice;
typedef StrictMock<ParametersMock> ParametersStrict;