#pragma once

#include <allegro5/allegro.h>

#include <string>
#include <unordered_map>

class TextureManager {
   public:
    static ALLEGRO_BITMAP* getTexture(const std::string& filePath);
    static void releaseAllTextures();

   private:
    static std::unordered_map<std::string, ALLEGRO_BITMAP*> textures;
};
