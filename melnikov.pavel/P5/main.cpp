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

  void solve();
  void scaleFromPoint(Shape &, point_t, double);
  void printFrame(Shape &);
  void printTotalFrame(Shape **, std::size_t);
}

int main()
{
  try
  {
    melnikov::solve();
  }
  catch (const std::invalid_argument &ex)
  {
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return 0;
}

namespace melnikov
{
  void solve()
  {
    Rectangle rectangle(4.0, 2.0, {1.0, 1.0});
    Xquare xquare(3.2, {0.0, 3.0});

    Shape *shapes[2] = {&rectangle, &xquare};

    std::cout << "Before:\n";

    std::size_t i = 0;
    double total_area = 0.0;

    for (Shape *const shape : shapes)
    {
      std::cout << "\t" << ++i << " area = " << shape->getArea() << ".\n";
      total_area += shape->getArea();
    }

    std::cout << "\tTotal area = " << total_area << ".\n\n";

    i = 0;
    for (Shape *const shape : shapes)
    {
      std::cout << "\t" << ++i << " frame: ";
      printFrame(*shape);
    }
    printTotalFrame(shapes, sizeof(shapes) / sizeof(shapes[0]));

    double x = 0.0;
    double y = 0.0;
    double k = 0.0;

    if (!(std::cin >> x >> y >> k) || !std::isfinite(x) || !std::isfinite(y) ||
        !std::isfinite(k))
    {
      throw std::invalid_argument(INV_INP);
    }

    for (Shape *const shape : shapes)
    {
      scaleFromPoint(*shape, {x, y}, k);
    }

    std::cout << "After:\n";

    i = 0;
    total_area = 0.0;

    for (Shape *const shape : shapes)
    {
      std::cout << "\t" << ++i << " area = " << shape->getArea() << ".\n";
      total_area += shape->getArea();
    }

    std::cout << "\tTotal area = " << total_area << ".\n\n";

    i = 0;
    for (Shape *const shape : shapes)
    {
      std::cout << "\t" << ++i << " frame: ";
      printFrame(*shape);
    }
    printTotalFrame(shapes, sizeof(shapes) / sizeof(shapes[0]));
  }

  void scaleFromPoint(Shape &shape, point_t point, double k)
  {
    shape.scale(k);
    shape.move(
      {point.x + k * (shape.getFrameRect().pos.x - point.x),
       point.y + k * (shape.getFrameRect().pos.y - point.y)});
  }

  void printFrame(Shape &shape)
  {
    const rectangle_t frame = shape.getFrameRect();

    std::cout << "width = " << frame.width << ", height = " << frame.height
              << ", pos_x = " << frame.pos.x << ", pos_y = " << frame.pos.y
              << ".\n";
  }

  void printTotalFrame(Shape **shapes, std::size_t count)
  {
    rectangle_t frame = shapes[0]->getFrameRect();

    double min_x = frame.pos.x - frame.width / 2.0;
    double max_x = frame.pos.x + frame.width / 2.0;
    double min_y = frame.pos.y - frame.height / 2.0;
    double max_y = frame.pos.y + frame.height / 2.0;

    for (std::size_t i = 1; i < count; ++i)
    {
      frame = shapes[i]->getFrameRect();

      const double minx = frame.pos.x - frame.width / 2.0;
      const double maxx = frame.pos.x + frame.width / 2.0;
      const double miny = frame.pos.y - frame.height / 2.0;
      const double maxy = frame.pos.y + frame.height / 2.0;

      min_x = (min_x < minx ? min_x : minx);
      max_x = (max_x > maxx ? max_x : maxx);
      min_y = (min_y < miny ? min_y : miny);
      max_y = (max_y > maxy ? max_y : maxy);
    }

    std::cout << "\tTotal frame: width = " << max_x - min_x
              << ", height = " << max_y - min_y
              << ", pos_x = " << (min_x + max_x) / 2.0
              << ", pos_y = " << (min_y + max_y) / 2.0 << "\n";
  }
}
