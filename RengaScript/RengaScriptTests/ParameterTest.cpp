#include "stdafx.h"
#include <RengaScript/ScriptRunner.h>

void CompareMetricParameter(const renga_script::AbstractParameter* pParameter, 
                            const wchar_t* expectedName, 
                            double expectedValue)
{
  auto pMetricParameter = dynamic_cast<const renga_script::MetricParameter*>(pParameter);
  ASSERT_NE(pMetricParameter, nullptr);
  EXPECT_EQ(pMetricParameter->name(), expectedName);
  EXPECT_DOUBLE_EQ(pMetricParameter->value(), expectedValue);
}

TEST(ParameterTest, shouldReadMetricParameter)
{
  renga_script::State state;
  renga_script::ScriptRunner runner(L".\\TestData\\MetricParameters.rso");
  ASSERT_TRUE(runner.run(state));
  ASSERT_EQ(state.getParametersCount(), 3);
  
  CompareMetricParameter(state.getParameter(0), L"Length", 400);
  CompareMetricParameter(state.getParameter(1), L"Width", 300);
  CompareMetricParameter(state.getParameter(2), L"Thickness", 10);
}