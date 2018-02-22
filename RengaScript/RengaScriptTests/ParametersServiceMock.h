#pragma once
#include <RengaScript/IParametersService.h>

class IParametersServiceMock : public renga_script::IParametersService
{
public:
  MOCK_METHOD1(setParameter, bool(renga_script::MetricParameter&));
};

typedef NiceMock<IParametersServiceMock> IParametersServiceNiceMock;
typedef StrictMock<IParametersServiceMock> IParametersServiceStrictMock;