#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "ParametersMock.h"
#include "Geometry2DBuilderMock.h"
#include "Geometry2DTypeStub.h"

class Geometry2DBuilderTest : public Test
{
public:
  void setUpGeometry2DBuilder(renga_script::IGeometry2DBuilder* pService)
  {
    m_context.pGeometryBuilder2D = pService;
  }

  void setUpParameters(renga_script::IParameters* pService)
  {
    m_context.pParameters = pService;
  }

protected:
  renga_script::Object3DConstructionContext m_context;
  
  Geometry2DBuilderStrict m_geometry2DStrictMock;
  Geometry2DBuilderNice m_geometry2DNiceMock;

  ParametersStrict m_parametersStrictMock;
  ParametersNice m_parametersNiceMock;
};

TEST_F(Geometry2DBuilderTest, shouldCreateRectByCoordinates)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createRect(0, 0, 200, 300)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = renga_script::executeScript(L".\\TestData\\Rect200x300.rso", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}

TEST_F(Geometry2DBuilderTest, shouldCreateRectByPoints)
{
  // given
  setUpGeometry2DBuilder(&m_geometry2DStrictMock);

  // expect
  EXPECT_CALL(m_geometry2DStrictMock, createRect(0, 0, 200, 300)).
    WillOnce(Return(new Curve2DStub()));

  // when
  bool result = renga_script::executeScript(L".\\TestData\\Rect200x300ByPoints.rso", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}