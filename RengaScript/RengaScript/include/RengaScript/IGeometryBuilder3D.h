#pragma once

namespace renga_script
{
  class IBody
  {

  };

  class IGeometryBuilder
  {
  public:
    virtual IBody* createExtrusionBody() = 0;
  };
}