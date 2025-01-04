#include "collision_helper.hpp"

bool CollisionHelper::isColliding(const SolidInterface& solid1, const SolidInterface& solid2) {
    const SolidRectangle* rect1 = dynamic_cast<const SolidRectangle*>(&solid1);
    const SolidRectangle* rect2 = dynamic_cast<const SolidRectangle*>(&solid2);
    const SolidCircle*    circ1 = dynamic_cast<const SolidCircle*>(&solid1);
    const SolidCircle*    circ2 = dynamic_cast<const SolidCircle*>(&solid2);

    if (rect1 && rect2) {
        return rect_vs_rect(*rect1, *rect2);
    } else if (rect1 && circ2) {
        return rect_vs_circle(*rect1, *circ2);
    } else if (circ1 && rect2) {
        return rect_vs_circle(*rect2, *circ1);
    } else if (circ1 && circ2) {
        return circle_vs_circle(*circ1, *circ2);
    } else {
        std::cerr << "Collision type not implemented" << std::endl;
        return false;
    }
}

bool CollisionHelper::rect_vs_rect(const SolidRectangle& rect1, const SolidRectangle& rect2) {
    return !(rect1.getPosition().getX() + rect1.getWidth() <= rect2.getPosition().getX() ||
             rect2.getPosition().getX() + rect2.getWidth() <= rect1.getPosition().getX() ||
             rect1.getPosition().getY() + rect1.getHeight() <= rect2.getPosition().getY() ||
             rect2.getPosition().getY() + rect2.getHeight() <= rect1.getPosition().getY());
}

bool CollisionHelper::rect_vs_circle(const SolidRectangle& rect, const SolidCircle& circle) {
    Position2D circle_center = circle.getPosition();
    float      rect_x        = rect.getPosition().getX();
    float      rect_y        = rect.getPosition().getY();

    float closest_x = std::max(rect_x, std::min(circle_center.getX(), rect_x + rect.getWidth()));
    float closest_y = std::max(rect_y, std::min(circle_center.getY(), rect_y + rect.getHeight()));

    float dx = circle_center.getX() - closest_x;
    float dy = circle_center.getY() - closest_y;

    return (pow(dx, 2) + pow(dy, 2) <= pow(circle.getRadius(), 2));
}

bool CollisionHelper::circle_vs_circle(const SolidCircle& circle1, const SolidCircle& circle2) {
    Position2D center1          = circle1.getPosition();
    Position2D center2          = circle2.getPosition();
    float      distance_squared = static_cast<float>(std::pow(center1.getX() - center2.getX(), 2)) +
                             static_cast<float>(std::pow(center1.getY() - center2.getY(), 2));
    return distance_squared <=
           static_cast<float>(std::pow(circle1.getRadius() + circle2.getRadius(), 2));
}
