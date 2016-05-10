//
//  Lazer.hpp
//  GameEngine
//
//  Created by Nigel Gilbert on 2/22/16.
//  Copyright © 2016 Nigel Gilbert. All rights reserved.
//

#ifndef LAZER_H
#define LAZER_H


#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Game.h"
#include <cstdlib>
#include <functional>

class Lazer : public WorldEntity
{
public:
    Lazer();
    
    bool isCulled;
    bool OnInitialize() override;
    
    void OnRender(const GameTime& time) override;
    void OnUpdate(const GameTime& time) override;
    void spawn(Vector3 translation, Vector3 rotation);
    void setCullCallback(Game*);

private:
    
    Game* parent;
    bool isOutOfScreen();
    void cull();
    Mesh* m_mesh;
    Material* m_material;
    Game* game;
    
};

#endif /* LAZER_H */