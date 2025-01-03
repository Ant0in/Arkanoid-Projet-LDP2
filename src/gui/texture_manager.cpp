#include "texture_manager.hpp"

#include <iostream>
#include <unistd.h>


std::unordered_map<std::string, ALLEGRO_BITMAP*> TextureManager::textures;

ALLEGRO_BITMAP* TextureManager::getTexture(const std::string& filePath) {
    // Check if texture is already loaded
    auto it = textures.find(filePath);
    if (it != textures.end()) {
        return it->second; // Return cached texture
    }

    // Load texture and store it
    ALLEGRO_BITMAP* texture = al_load_bitmap(filePath.c_str());
    if (!texture) {
        std::cerr << "Erreur : Impossible de charger la texture : " << filePath << std::endl;
        return nullptr;
    }

    textures[filePath] = texture;
    return texture;
}

void TextureManager::releaseAllTextures() {
    
    for (auto& pair : textures) {
        if (pair.second) {
            al_destroy_bitmap(pair.second);
            pair.second = nullptr;
        }
    }
    
    textures.clear();
}