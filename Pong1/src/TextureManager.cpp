//
//  TextureManager.cpp
//  Pong1
//
//  Created by Anaida Gasparyan on 12/2/18.
//  Copyright © 2018 Pong1. All rights reserved.
//

#include "TextureManager.h"

bool TextureManager::load(const std::string &fileName, const std::string &key, SDL_Renderer* pRenderer) {
    
    // TODO add support for other types of images
    // SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    SDL_Surface* pTempSurface = SDL_LoadBMP(fileName.c_str());
    if (pTempSurface == 0) {
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    
    if (pTexture == 0) {
        return false;
    }
    
    m_textureMap[key] = pTexture;
    return true;
}
