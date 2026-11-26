#ifndef MELNIKOV_RECTANGLE_HPP
#define MELNIKOV_RECTANGLE_HPP

#include "shape.hpp"

namespace melnikov
{
  class Rectangle : public Shape {
  public:
    Rectangle(double, double, point_t);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double, double) override;
    void move(point_t) override;
    void scale(double) override;

  private:
    rectangle_t data_;
  };
}

#endif
