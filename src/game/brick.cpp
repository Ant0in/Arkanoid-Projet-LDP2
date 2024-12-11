#include "brick.hpp"

class Brick{
    private:
        Position2D position;
        float width, height;
        BrickType btype;
        SolidCircle hitbox = SolidRectangle(position, height, width);
        int hp = attributeBrickHpByType(btype);
    public:
        Brick(Position2D position, float width, float height, BrickType btype): position{position}, width{width}, height{height}{};

        static int attributeBrickHpByType(BrickType type){
            switch (btype) {
                case BrickType::GOLD:
                    return std::numeric_limits<int>::infinity();
                case BrickType::SILVER:
                    return 2; 
                default:
                    return 1; 
    }
        }

        Position2D getPosition() {return position;}
        void setPosition(Position2D pos) {position = pos;}

        float getHeight() {return height;}
        float getWidth() {return width;}

        void setHeight(float h) {height = h;}
        void setWidth(float w) {width = w;}

        BrickType getBrickType() {return btype;}
        
        int getHP() {return hp;}
        void setHP(int v) {hp =v;}

        SolidRectangle getHitbox() {return hitbox;}

        void moveToCoordinates(Position2D coord){
            // Move brick with its hitbox
            setPosition(coord);
            getHitbox().setPosition(coord);
        }

        void makeBrickLooseHP(int loss){
            int new_hp = getHP() - loss;
            setHP(new_hp);
        }

        bool isBroken(){
            return getHP() <= 0;
        }

        int getBrickValue(){
            switch (getBrickType()) {
                case BrickType::WHITE: return 50;
                case BrickType::ORANGE: return 60;
                case BrickType::CYAN: return 70;
                case BrickType::GREEN: return 80;
                case BrickType::RED: return 90;
                case BrickType::BLUE: return 100;
                case BrickType::MAGENTA: return 110;
                case BrickType::YELLOW: return 120;
                case BrickType::SILVER: return 200;
                default: 
                    std::cerr << "Brick type not implemented" << std::endl;
                    return 1;
        }

        bool operator==(Brick other){
            return (getPositon().getX() == other.getPosition().getX()) && (getPositon().getY() == other.getPosition().getY());
        }
};