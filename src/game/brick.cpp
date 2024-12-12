#include "brick.hpp"

class Brick{
    private:
        Position2D position;
        float width, height;
        BrickType btype;
        SolidRectangle hitbox;
        int hp;
    public:
        Brick(const Position2D& position, float width, float height, BrickType btype): position{position}, width{width}, height{height}, btype{btype}, hitbox{SolidRectangle(position, width, height)}, hp{attributeBrickHpByType(btype)}{};

        static int attributeBrickHpByType(BrickType type){
            switch (type) {
                case BrickType::GOLD:
                    return std::numeric_limits<int>::max();
                case BrickType::SILVER:
                    return 2; 
                default:
                    return 1; 
            }
        }

        Position2D getPosition() const {return position;}
        void setPosition(const Position2D& pos) {position = pos;}

        float getHeight() const {return height;}
        float getWidth() const {return width;}

        void setHeight(float h) {height = h;}
        void setWidth(float w) {width = w;}

        BrickType getBrickType() const {return btype;}
        
        int getHP() const {return hp;}
        void setHP(int v) {hp =v;}

        SolidRectangle& getHitbox() {return hitbox;}
        const SolidRectangle& getHitbox() const {return hitbox;}

        void moveToCoordinates(const Position2D& coord){
            // Move brick with its hitbox
            setPosition(coord);
            getHitbox().setPosition(coord);
        }

        void makeBrickLoseHP(int loss){
            int new_hp = getHP() - loss;
            setHP(new_hp);
        }

        bool isBroken() const {
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
                    return 0;
            }
        }

        bool operator==(const Brick& other) const {
            return (getPosition().getX() == other.getPosition().getX()) && (getPosition().getY() == other.getPosition().getY());
        }
};