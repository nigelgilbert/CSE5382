//
//  WorldEntity.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef WORLDENTITY_H
#define WORLDENTITY_H

#include "GameObject.h"
#include "Transform.h"
#include <vector>

using namespace std;

class WorldEntity : public GameObject
{
public:
    Transform Transform;
    BoundingSphere bounds;
};


#endif /* WorldEntity_hpp */
