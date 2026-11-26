#ifndef XQUARE_HPP
#define XQUARE_HPP

#include "shape.hpp"

namespace melnikov
{
  class Xquare : public Shape
  {
  public:
    Xquare(double, point_t);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double, double) override;
    void move(point_t) override;
    void scale(double) override;

  private:
    xquare_t data_;
  };
}

#endif
