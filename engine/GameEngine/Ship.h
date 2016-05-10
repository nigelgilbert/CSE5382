//
//  Ship.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef SHIP_H
#define SHIP_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Game.h"

class Ship : public WorldEntity
{
public:
    float radius;
    Ship()
    {
        radius = .5;
    }
    
    bool OnInitialize() override;
    void reset();
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
private:
    void wrap();
    Mesh* m_mesh;
    Material* m_material;
    Game* game;
    
};

#endif /* Ship_hpp */
