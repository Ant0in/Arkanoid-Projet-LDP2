#pragma once

#include <unordered_map>
#include <string>
#include <allegro5/allegro.h>


class TextureManager {

    public:

        static ALLEGRO_BITMAP* getTexture(const std::string& filePath);
        static void releaseAllTextures();

    private:

        static std::unordered_map<std::string, ALLEGRO_BITMAP*> textures;
        
};
