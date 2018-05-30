#pragma once

#include <RengaScript/IObject3DDefinition.h>

class Object3DDefinitionMock : public IObject3DDefinition
{
public:
  MOCK_METHOD1(setSolidRepresentation, void(const ISolid* pSolid));
};

typedef NiceMock<Object3DDefinitionMock> Object3DDefinitionMockNice;
typedef StrictMock<Object3DDefinitionMock> Object3DDefinitionMockStrict;
