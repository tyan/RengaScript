#pragma once

namespace renga_script
{
  class Point2D
  {
  public:
    double x;
    double y;
  };


  class LineSegment
  {
  public:
    Point2D p1;
    Point2D p2;
  };

  class Arc
  {
  public:
    Point2D c;
    double angle1;
    double angle2;
    bool isClockwise;
  };
}
