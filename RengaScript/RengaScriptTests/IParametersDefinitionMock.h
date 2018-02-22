#pragma once
#include <RengaScript/IParametersDefinition.h>

class IParametersDefinitionMock : public renga_script::IParametersDefinition
{
public:
  MOCK_METHOD1(setParameter, bool(renga_script::MetricParameter&));
};

typedef NiceMock<IParametersDefinitionMock> IParametersDefinitionNiceMock;
typedef StrictMock<IParametersDefinitionMock> IParametersDefinitionStrictMock;