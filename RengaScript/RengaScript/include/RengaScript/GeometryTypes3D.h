#pragma once

namespace renga_script
{
  class Point3D
  {
  public:
    double x;
    double y;
    double z;
  };

  class Vector3D
  {
  public:
    double x;
    double y;
    double z;
  };

  class LCS3D
  {
  public:
    Point3D c;
    Vector3D ox;
    Vector3D oy;
  };
}