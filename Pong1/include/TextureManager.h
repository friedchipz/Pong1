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

using namespace std;

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
    bool load(const string &fileName, const string &key, SDL_Renderer* pRenderer);

    //TODO return texture by id
    SDL_Texture* getTexture(string id) { return m_textureMap[id]; }
    
private:
    map<string, SDL_Texture*> m_textureMap;
};

#endif /* TextureManager_h */
