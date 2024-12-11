#include "collision_helper.hpp"

class CollisionHelper{
    static bool isColliding(SolidInterface solid1, SolidInterface solid2){
        if (dynamic_cast<SolidRectangle*>(solid1) && dynamic_cast<SolidRectangle*>(solid2)){
            return CollisionHelper.rect_vs_rect(solid1, solid2);
        }
        else if (dynamic_cast<SolidRectangle*>(solid1) && dynamic_cast<SolidCircle*>(solid2)){
            return CollisionHelper.rect_vs_circle(solid1, solid2);
        }
        else if (dynamic_cast<SolidCircle*>(solid1) && dynamic_cast<SolidRectangle*>(solid2)){
            return CollisionHelper.rect_vs_circle(solid2, solid1);
        }
        else if (dynamic_cast<SolidCircle*>(solid1) && dynamic_cast<SolidCircle*>(solid2)){
            return CollisionHelper.circle_vs_circle(solid1, solid2);
        }
        else{
            std::cerr << "Not implemented" << std::endl;
            return 1;
        }
    }

    static bool rect_vs_rect(SolidRectangle rect1, SolidRectangle rect2){
        return !(rect1.getPosition().getX() + rect1.getWidth() <= rect2.getPosition().getX() ||
            rect2.getPosition().getX() + rect2.getWidth() <= rect1.getPosition().getX() ||
            rect1.getPosition().getY() + rect1.getHeight() <= rect2.getPosition().getY() ||
            rect2.getPosition().getY() + rect2.getHeight() <= rect1.getPosition().getY());
    }

    static bool rect_vs_circle(SolidRectangle rect, SolidCircle circle){
        Position2D circle_center = circle.getPosition();
        float rect_x = rect.getPosition().getX();
        float rect_x = rect.getPosition().getY();

        float closest_x = std::max(rect_x, min(circle_center.getX(), rect_x + rect.getWidth()));
        float closest_y = std::max(rect_y, min(circle_center.getY(), rect_y + rect.getHeight()));

        float dx = circle_center.getX() - closest_x;
        float dy = circle_center.getY() - closest_y;

        return (pow(dx, 2) + pow(dy, 2) <= pow(circle.getRadius(), 2));
    }

    static bool circle_vs_circle(SolidCircle circle1, SolidCircle circle2){
        Position2D center1 = circle1.getPosition();
        Position2D center2 = circle2.getPosition();
        float distance_squared = pow((center1.getX() - center2.getX()), 2) + pow((center1.getY() - center2.getY()), 2);
        return distance_squared <= pow((circle1.getRadius() + circle2.getRadius()), 2);
    }
};