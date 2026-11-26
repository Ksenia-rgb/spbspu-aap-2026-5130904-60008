
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "rectangle.hpp"
#include "xquare.hpp"

namespace melnikov
{
  const std::string INV_INP = "Invalid input";

  constexpr double rectangleWidth = 4.0;
  constexpr double rectangleHeight = 2.0;
  constexpr double xquareSide = 3.2;
  constexpr double two = 2.0;

  void solve();
  void scaleFromPoint(Shape &, point_t, double);
  void printFrame(Shape &);
  void printTotalFrame(Shape **, std::size_t);
}

int main()
{
  try {
    melnikov::solve();
  } catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return 0;
}

namespace melnikov
{
  void solve()
  {
    Rectangle rectangle(rectangleWidth, rectangleHeight, {1.0, 1.0});
    Xquare xquare(xquareSide, {0.0, 3.0});

    Shape *shapes[2] = {&rectangle, &xquare};

    std::cout << "Before:\n";

    std::size_t i = 0;
    double totalArea = 0.0;

    for (Shape *shape : shapes) {
      std::cout << "\t" << ++i << " area = " << shape->getArea() << ".\n";
      totalArea += shape->getArea();
    }

    std::cout << "\tTotal area = " << totalArea << ".\n\n";

    i = 0;
    for (Shape *shape : shapes) {
      std::cout << "\t" << ++i << " frame: ";
      printFrame(*shape);
    }
    printTotalFrame(shapes, sizeof(shapes) / sizeof(shapes[0]));

    double x = 0.0;
    double y = 0.0;
    double k = 0.0;

    if (!(std::cin >> x >> y >> k) || !std::isfinite(x) ||
        !std::isfinite(y) || !std::isfinite(k))
    {
      throw std::invalid_argument(INV_INP);
    }

    for (Shape *shape : shapes) {
      scaleFromPoint(*shape, {x, y}, k);
    }

    std::cout << "After:\n";

    i = 0;
    totalArea = 0.0;

    for (Shape *shape : shapes) {
      std::cout << "\t" << ++i << " area = " << shape->getArea() << ".\n";
      totalArea += shape->getArea();
    }

    std::cout << "\tTotal area = " << totalArea << ".\n\n";

    i = 0;
    for (Shape *shape : shapes) {
      std::cout << "\t" << ++i << " frame: ";
      printFrame(*shape);
    }
    printTotalFrame(shapes, sizeof(shapes) / sizeof(shapes[0]));
  }

  void scaleFromPoint(Shape &shape, point_t point, double k)
  {
    shape.scale(k);
    shape.move({point.x + k * (shape.getFrameRect().pos.x - point.x),
                point.y + k * (shape.getFrameRect().pos.y - point.y)});
  }

  void printFrame(Shape &shape)
  {
    const rectangle_t frame = shape.getFrameRect();

    std::cout << "width = " << frame.width << ", height = " << frame.height
              << ", pos_x = " << frame.pos.x
              << ", pos_y = " << frame.pos.y << ".\n";
  }

  void printTotalFrame(Shape **shapes, std::size_t count)
  {
    rectangle_t frame = shapes[0]->getFrameRect();
    double minX = frame.pos.x - frame.width / two;
    double maxX = frame.pos.x + frame.width / two;
    double minY = frame.pos.y - frame.height / two;
    double maxY = frame.pos.y + frame.height / two;

    for (std::size_t i = 1; i < count; ++i) {
      frame = shapes[i]->getFrameRect();

      const double minx = frame.pos.x - frame.width / two;
      const double maxx = frame.pos.x + frame.width / two;
      const double miny = frame.pos.y - frame.height / two;
      const double maxy = frame.pos.y + frame.height / two;

      minX = (minX < minx ? minX : minx);
      maxX = (maxX > maxx ? maxX : maxx);
      minY = (minY < miny ? minY : miny);
      maxY = (maxY > maxy ? maxY : maxy);
    }

    std::cout << "\tTotal frame: width = " << maxX - minX
              << ", height = " << maxY - minY
              << ", pos_x = " << (minX + maxX) / two
              << ", pos_y = " << (minY + maxY) / two << "\n";
  }
}

