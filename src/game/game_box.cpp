#include "game_box.hpp"

class GameBox{
    private:
        Position2D position;
        float width, height;

        std::vector<Ball> balls;
        Racket racket;
        std::vector<Brick> bricks;
        std::vector<SolidInterface> entities;
    public:
        GameBox(Position2D position, float width, float height, std::vector<Ball> balls, Racket racket, std::vector<SolidInterface> entities): position{position}, width{width}, height{height}, balls{balls}, racket{racket}, entities{entities}{};

        Position2D getPosition() {return position;}

        float getWidth() {return width;}
        float getHeight() {return height;}

        std::vector<Brick> getBricks() {return bricks;}

        void addBrick(Brick brick){
            getBricks().push_back(brick);
        }
        void removeBrick(Brick brick){
            for (auto it = getBricks().begin(); it != getBricks().end(); ++it) {
                if (*it == brick) { 
                    getBricks().erase(it); 
                    break;
                }
            }
        }

        std::vector<Ball> getBalls() {return balls;}

        Racket getRacket() {return racket;}

        std::vector<SolidInterface> getEntities() {return entities;}

        void addEntity(SolidInterface entity){
            getEntities().push_back(entity);
        }
        void removeEntity(SolidInterface entity){
            for (auto it = getEntities().begin(); it != getEntities().end(); ++it) {
                if (*it == entity) { 
                    getEntities().erase(it); 
                    break;
                }
            }
        }

        bool tryMoveRacket(Position2D p);

        std::vector<bool> tryMoveBalls(std::vector<Position2D> p_vec);

        void checkCollisionWithWalls();

        std::vector<Brick> checkCollisionsWithRaquetteAndBricks();
};