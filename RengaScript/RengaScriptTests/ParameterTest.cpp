#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ScriptRunner.h>

#include "ParametersServiceMock.h"

class ParametersDefinitionTest : public Test
{
public:
  renga_script::Object3DConstructionContext createContext(renga_script::IParametersService* pParametersService)
  {
    renga_script::Object3DConstructionContext context;
    context.pParameters = pParametersService;
    return context;
  }
  
protected:
  IParametersServiceStrictMock m_parametersStrictMock;
  IParametersServiceNiceMock m_parametersNiceMock;
};


TEST_F(ParametersDefinitionTest, shouldReadMetricParameters)
{
  // given
  renga_script::ScriptRunner runner(L".\\TestData\\LengthAndWidthParameters.rso");
  renga_script::MetricParameter lengthParameter(L"", 0);
  renga_script::MetricParameter widthParameter(L"", 0);

  // expect
  Sequence s;
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&lengthParameter), Return(true)));
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&widthParameter), Return(true)));

  // when
  bool result = runner.run(createContext(&m_parametersStrictMock));
  
  // then
  EXPECT_EQ(result, true);
  
  EXPECT_EQ(lengthParameter.name(), L"Length");
  EXPECT_DOUBLE_EQ(lengthParameter.value(), 400.0);
  
  EXPECT_EQ(widthParameter.name(), L"Width");
  EXPECT_DOUBLE_EQ(widthParameter.value(), 300.0);
}