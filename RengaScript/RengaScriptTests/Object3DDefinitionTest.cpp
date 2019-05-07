#include "stdafx.h"
#include <RengaScript/Parameter.h>
#include <RengaScript/ExecuteScript.h>

#include "GeometryBuilderMock.h"
#include "Object3DDefinitionMock.h"
#include "GeometryTypeStub.h"
#include "GeometryTypeMatcher.h"

class LuaObject3DDefinitionTest : public Test
{
public:
  void setUpContext(IGeometryBuilder* pGeometryBuilder, IObject3DDefinition* pObject3DDefinition)
  {
    m_context.pGeometryBuilder = pGeometryBuilder;
    m_context.pObject3DDefinition = pObject3DDefinition;
  }

protected:
  Object3DConstructionContext m_context;

  GeometryBuilderStrict m_geometryBuilderStrict;
  GeometryBuilderNice m_geometryBuilderNice;

  Object3DDefinitionMockStrict m_object3DDefinitionStrict;
  Object3DDefinitionMockNice m_object3DDefinitionNice;
};

TEST_F(LuaObject3DDefinitionTest, shouldSetCubeSolid)
{
  // given
  setUpContext(&m_geometryBuilderNice, &m_object3DDefinitionStrict);
  int solidId = 42;

  ON_CALL(m_geometryBuilderNice, createCuboid(_, _)).
    WillByDefault( Return( new SolidStub(solidId)));

  // expect
  EXPECT_CALL(m_object3DDefinitionStrict, setSolidRepresentation(SolidIdEqConst(solidId)));

  // when
  bool result = executeLuaScript(L".\\TestData\\SetObject3DSolidRepresentation_Cube.lua", m_context);

  // then
  EXPECT_TRUE(result) << m_context.error;
}