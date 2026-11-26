#include <cmath>
#include <stdexcept>
#include <string>

#include "xquare.hpp"

const std::string INV_SIDE = "Invalid xquare side";
const std::string INV_COORDS = "Invalid coordinates";
const std::string INV_SCALE_FAC = "Invalid scale factor";

namespace melnikov
{
  Xquare::Xquare(double side, point_t center) : data_{side, center}
  {
    if (!std::isfinite(side) || side <= 0.0) {
      throw std::invalid_argument(INV_SIDE);
    }
    if (!std::isfinite(center.x) || !std::isfinite(center.y)) {
      throw std::invalid_argument(INV_COORDS);
    }
  }

  double Xquare::getArea() const
  {
    return data_.side * data_.side;
  }

  rectangle_t Xquare::getFrameRect() const
  {
    const double frameSide = data_.side * std::sqrt(2.0);
    return rectangle_t{frameSide, frameSide, data_.pos};
  }

  void Xquare::move(double dx, double dy)
  {
    if (!std::isfinite(dx) || !std::isfinite(dy)) {
      throw std::invalid_argument(INV_COORDS);
    }
    data_.pos.x += dx;
    data_.pos.y += dy;
  }

  void Xquare::move(point_t center)
  {
    if (!std::isfinite(center.x) || !std::isfinite(center.y)) {
      throw std::invalid_argument(INV_COORDS);
    }
    data_.pos = center;
  }

  void Xquare::scale(double k)
  {
    if (!std::isfinite(k) || k <= 0.0) {
      throw std::invalid_argument(INV_SCALE_FAC);
    }
    data_.side *= k;
  }
}
