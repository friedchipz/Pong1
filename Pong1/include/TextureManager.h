//
//  TextureManager.h
//  Pong1
//
//  Created by Anaida Gasparyan on 12/2/18.
//  Copyright © 2018 Pong1. All rights reserved.
//

#ifndef TextureManager_h
#define TextureManager_h

#include <SDL.h>
#include <string>
#include <map>

class TextureManager {
    
// Start Singleton
public:
    static TextureManager& Instance() {
        static TextureManager instance;
        return instance;
    }
    TextureManager(TextureManager const&) = delete;
    TextureManager& operator=(TextureManager const&) = delete;
private:
    TextureManager(){}
// End Singleton
    
public:
    bool load(const std::string &fileName, const std::string &key, SDL_Renderer* pRenderer);

    //TODO return texture by id
    SDL_Texture* getTexture(std::string id) { return m_textureMap[id]; }
    
private:
    std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif /* TextureManager_h */
