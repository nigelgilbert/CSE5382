//
//  BoundingSphere.cpp
//  GameEngine
//
//  Created by Nigel Gilbert on 4/4/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "BoundingSphere.h"
#include <iostream>

BoundingSphere::BoundingSphere()
{
    radius = 0.0;
    center = Vector3(0,0,0);
};

bool BoundingSphere::intersects(BoundingSphere& other)
{
    float pythagorean = center.distance(other.center);
    if (pythagorean - (other.radius + radius) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BoundingSphere::initialize(vector<Vector3> vertices)
{
    float furthest = 0.0;
    float distToPoint = 0.0;
    
    for (auto vertex : vertices)
    {
        distToPoint = vertex.magnitude();
        if (distToPoint > furthest)
            furthest = distToPoint;
    }
    
    radius = distToPoint;
}