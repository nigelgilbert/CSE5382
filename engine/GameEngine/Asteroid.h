//
//  Asteroid.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Game.h"
#include <cstdlib>

class Asteroid : public WorldEntity
{
public:
    Asteroid() {}
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    void spawn();
    void destroy();
    
private:
    void wrap();
    Mesh* m_mesh;
    Material* m_material;
    Game* game;
    
};

#endif /* Asteroid_hpp */
