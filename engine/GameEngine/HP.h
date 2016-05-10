//
//  HP.hpp
//  GameEngine
//
//  Created by Nigel Gilbert on 5/9/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef HP_h
#define HP_h

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Game.h"

class HPShip : public WorldEntity
{
public:
    float radius;
    HPShip()
    {
        radius = .5;
    }
    
    bool OnInitialize() override;
    void OnRender(const GameTime& time) override;
    
private:
    Mesh* m_mesh;
    Material* m_material;
    Game* game;
    
};

#endif /* HP_h */
