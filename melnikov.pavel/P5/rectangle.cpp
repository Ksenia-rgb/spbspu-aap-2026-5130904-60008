
#include <cmath>
#include <stdexcept>
#include <string>

#include "rectangle.hpp"

const std::string INV_WIDTH = "Invalid rectangle width";
const std::string INV_HEIGHT = "Invalid rectangle height";
const std::string INV_COORDS = "Invalid coordinates";
const std::string INV_SCALE_FAC = "Invalid scale factor";

namespace melnikov
{
  Rectangle::Rectangle(double width, double height, point_t center):
    data_{width, height, center}
  {
    if (!std::isfinite(width) || width <= 0.0) {
      throw std::invalid_argument(INV_WIDTH);
    }
    if (!std::isfinite(height) || height <= 0.0) {
      throw std::invalid_argument(INV_HEIGHT);
    }
    if (!std::isfinite(center.x) || !std::isfinite(center.y)) {
      throw std::invalid_argument(INV_COORDS);
    }
  }

  double Rectangle::getArea() const
  {
    return data_.height * data_.width;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return data_;
  }

  void Rectangle::move(double dx, double dy)
  {
    if (!std::isfinite(dx) || !std::isfinite(dy)) {
      throw std::invalid_argument(INV_COORDS);
    }
    data_.pos.x += dx;
    data_.pos.y += dy;
  }

  void Rectangle::move(point_t center)
  {
    if (!std::isfinite(center.x) || !std::isfinite(center.y)) {
      throw std::invalid_argument(INV_COORDS);
    }
    data_.pos = center;
  }

  void Rectangle::scale(double k)
  {
    if (!std::isfinite(k) || k <= 0.0) {
      throw std::invalid_argument(INV_SCALE_FAC);
    }
    data_.height *= k;
    data_.width *= k;
  }
}

