#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "ParametersServiceMock.h"

class ParametersTest : public Test
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


TEST_F(ParametersTest, shouldReadMetricParameters)
{
  // given
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
  bool result = renga_script::executeScript(L".\\TestData\\LengthAndWidthParameters.rso", createContext(&m_parametersStrictMock));
  
  // then
  EXPECT_EQ(result, true);
  
  EXPECT_EQ(lengthParameter.name(), L"Length");
  EXPECT_DOUBLE_EQ(lengthParameter.value(), 400.0);
  
  EXPECT_EQ(widthParameter.name(), L"Width");
  EXPECT_DOUBLE_EQ(widthParameter.value(), 300.0);
}

TEST_F(ParametersTest, shouldFailExecutionIfSettingParameterFailed)
{
  // given
  ON_CALL(m_parametersStrictMock, setParameter(_)).WillByDefault(Return(false));

  // when
  bool result = renga_script::executeScript(L".\\TestData\\LengthAndWidthParameters.rso", createContext(&m_parametersNiceMock));

  // then
  EXPECT_EQ(result, false);
}

TEST_F(ParametersTest, shouldFailWhenParametersServiceNorSupported)
{
  // given
  ON_CALL(m_parametersStrictMock, setParameter(_)).WillByDefault(Return(true));

  // when
  bool result = renga_script::executeScript(L".\\TestData\\LengthAndWidthParameters.rso", createContext(nullptr));

  // then
  EXPECT_EQ(result, false);
}