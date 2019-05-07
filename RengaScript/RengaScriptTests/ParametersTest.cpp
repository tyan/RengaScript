#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "ParametersMock.h"

class ParametersTest : public Test
{
public:
  void setupContext(IParameters* pParameters)
  {
    m_context.pParameters = pParameters;
  }

protected:
  typedef std::function<bool(Object3DConstructionContext& context)> ExecuteScriptFunc;
  
  void shouldReadMetricParametersImpl(ExecuteScriptFunc executeScript)
  {
    // given
    MetricParameter lengthParameter(L"", 0);
    MetricParameter widthParameter(L"", 0);

    setupContext(&m_parametersStrictMock);

    // expect
    Sequence s;
    EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
      InSequence(s).
      WillOnce(DoAll(SaveArg<0>(&lengthParameter), Return(true)));
    EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
      InSequence(s).
      WillOnce(DoAll(SaveArg<0>(&widthParameter), Return(true)));

    // when
    bool result = executeScript(m_context);

    // then
    ASSERT_EQ(result, true) << std::endl << "CONTEXT ERROR: " << m_context.error << std::endl;

    EXPECT_EQ(lengthParameter.name(), L"Length");
    EXPECT_DOUBLE_EQ(lengthParameter.value(), 400.0);

    EXPECT_EQ(widthParameter.name(), L"Width");
    EXPECT_DOUBLE_EQ(widthParameter.value(), 300.0);
  }

protected:
  Object3DConstructionContext m_context;

  ParametersStrict m_parametersStrictMock;
  ParametersNice m_parametersNiceMock;
};


TEST_F(ParametersTest, shouldReadMetricParameters_lua)
{
  auto executeScriptFunction = std::bind(executeLuaScript, L".\\TestData\\LengthAndWidthParameters.lua", std::placeholders::_1);
  shouldReadMetricParametersImpl(executeScriptFunction);
}

TEST_F(ParametersTest, shouldReadMetricParameters_py)
{
  auto executeScriptFunction = std::bind(executePyScript, L".\\TestData\\LengthAndWidthParameters.py", std::placeholders::_1);
  shouldReadMetricParametersImpl(executeScriptFunction);
}

TEST_F(ParametersTest, shouldReadMetricParametersWithCategory)
{
  // given
  MetricParameter lengthParameter(L"", 0, L"");
  MetricParameter widthParameter(L"", 0, L"");

  setupContext(&m_parametersStrictMock);

  // expect
  Sequence s;
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&lengthParameter), Return(true)));
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&widthParameter), Return(true)));

  // when
  bool result = executeLuaScript(L".\\TestData\\LengthAndWidthParametersWithCategory.lua", m_context);

  // then
  ASSERT_EQ(result, true);

  EXPECT_EQ(lengthParameter.name(), L"Length");
  EXPECT_DOUBLE_EQ(lengthParameter.value(), 400.0);
  EXPECT_EQ(lengthParameter.category(), L"Category1");

  EXPECT_EQ(widthParameter.name(), L"Width");
  EXPECT_DOUBLE_EQ(widthParameter.value(), 300.0);
  EXPECT_EQ(widthParameter.category(), L"Category2");
}

TEST_F(ParametersTest, shouldFailExecutionIfSettingParameterFailed)
{
  // given
  setupContext(&m_parametersNiceMock);
  ON_CALL(m_parametersNiceMock, setParameter(_)).WillByDefault(Return(false));

  // when
  bool result = executeLuaScript(L".\\TestData\\LengthAndWidthParameters.lua", m_context);

  // then
  EXPECT_EQ(result, false);
}

TEST_F(ParametersTest, shouldFailWhenParametersServiceNorSupported)
{
  // given
  ON_CALL(m_parametersStrictMock, setParameter(_)).WillByDefault(Return(true));

  // when
  bool result = executeLuaScript(L".\\TestData\\LengthAndWidthParameters.lua", m_context);

  // then
  EXPECT_EQ(result, false);
}

TEST_F(ParametersTest, shouldParameterReturnValue)
{
  // given
  MetricParameter LParameter(L"", 0.0);
  MetricParameter WParameter(L"", 0.0);

  setupContext(&m_parametersStrictMock);

  // expect
  Sequence s;
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&LParameter), Return(true)));
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&WParameter), Return(true)));

  // when
  bool result = executeLuaScript(L".\\TestData\\WParamDefinedByLParam.lua", m_context);

  // then
  ASSERT_EQ(result, true);
  EXPECT_DOUBLE_EQ(LParameter.value(), 400.0);
  EXPECT_DOUBLE_EQ(LParameter.value(), WParameter.value());
}

TEST_F(ParametersTest, valueCanBeSetToParameter)
{
  // given
  MetricParameter LParameter(L"", 0.0);
  MetricParameter WParameter(L"", 0.0);

  setupContext(&m_parametersStrictMock);

  // expect
  Sequence s;
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&LParameter), Return(true)));
  EXPECT_CALL(m_parametersStrictMock, setParameter(_)).
    InSequence(s).
    WillOnce(DoAll(SaveArg<0>(&WParameter), Return(true)));

  // when
  bool result = executeLuaScript(L".\\TestData\\WParamDefinedByLParam2.lua", m_context);

  // then
  ASSERT_EQ(result, true);
  EXPECT_DOUBLE_EQ(LParameter.value(), 400);
  EXPECT_DOUBLE_EQ(WParameter.value(), 200);
}