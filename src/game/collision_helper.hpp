#include "common.hpp"
#include "solid_shapes.hpp"
#include <iostream>
#include <cmath>

class CollisionHelper{
    static bool isColliding(SolidInterface solid1, SolidInterface solid2);

    static bool rect_vs_rect(SolidRectangle rect1, SolidRectangle rect2);

    static bool rect_vs_circle(SolidRectangle rect, SolidCircle circle);

    static bool circle_vs_circle(SolidCircle circle1, SolidCircle circle2);
};