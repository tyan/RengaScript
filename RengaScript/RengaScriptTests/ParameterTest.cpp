#include "stdafx.h"
#include <RengaScript/ScriptRunner.h>

TEST(ParameterTest, shouldReadMetricParameter)
{
  renga_script::ScriptRunner runner(L".\\TestData\\plate.rso");
  runner.run();
  EXPECT_TRUE(true);
}