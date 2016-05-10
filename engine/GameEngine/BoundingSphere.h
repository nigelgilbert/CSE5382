//
//  BoundingSphere.hpp
//  GameEngine
//
//  Created by Nigel Gilbert on 4/4/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include <stdio.h>
#include <vector>
#include "vectors.h"

using namespace std;

class BoundingSphere {
public:
    float radius;
    Vector3 center;
    
    BoundingSphere();
    bool intersects(BoundingSphere& other);
    void initialize(vector<Vector3> vertices);
    
};
        
#endif /* BoundingSphere_hpp */
