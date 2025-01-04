#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../common.hpp"
#include "solid_shapes.hpp"

class CollisionHelper {
   public:
    static bool isColliding(const SolidInterface& solid1, const SolidInterface& solid2);
    static bool rect_vs_rect(const SolidRectangle& rect1, const SolidRectangle& rect2);
    static bool rect_vs_circle(const SolidRectangle& rect, const SolidCircle& circle);
    static bool circle_vs_circle(const SolidCircle& circle1, const SolidCircle& circle2);
};