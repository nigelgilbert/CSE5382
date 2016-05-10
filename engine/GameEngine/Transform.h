//
//  Transform.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Common.h"
#include "GameObject.h"
#include "Vectors.h"
#include "Matrix.h"
#include "BoundingSphere.h"


class Transform
{
public:
    Vector3 Translation;
    Vector3 Rotation;
    Vector3 Scale;
    
    // verlet physics
    Vector3 Push;
    Vector3 Spin;
    float Drag;
    Vector3 PreviousTranslation;
    Vector3 PreviousRotation;
    float PreviousFrameTime;
    
    Transform()
    {
        Scale.X = Scale.Y = Scale.Z = 1;
        Drag = .99;
    }
    
    Matrix GetMatrix()
    {
        auto mt = Matrix::CreateTranslation(Translation);
        auto mr = Matrix::CreateRotation(Rotation);
        auto ms = Matrix::CreateScale(Scale);
        auto result = mr * mt * ms;
        return result;
    }
    
    void reset()
    {
        Vector3 zero(0,0,0);
        Translation = zero;
        Rotation = zero;
        Push = zero;
        Spin = zero;
        PreviousTranslation = zero;
        PreviousRotation = zero;
    }
    
    void setPrevious()
    {
        PreviousTranslation = Translation;
        PreviousRotation = Rotation;
    }
    
    float getTimeScale(const GameTime& time)
    {
        auto scale = time.TotalSeconds() - PreviousFrameTime;
        PreviousFrameTime = time.TotalSeconds();
        return scale;
    }
    
    void Verlet(const float& ts)
    {
        Translation += getPush(ts);
        Rotation += getSpin(ts);
    }
    
    void moveUp(const double& scaler)
    {
        Translation += GetMatrix().Up() * scaler;
    }
    
    void moveYaw(const double& scaler)
    {
        Rotation.Z += scaler;
    }
    
    void scaleSphere(BoundingSphere& sphere)
    {
        // h is the hemisphere point, c is the center
        Vector4 h(sphere.center.X + sphere.radius, sphere.center.Y, sphere.center.Z, 1);
        Vector4 c(sphere.center.X, sphere.center.Y, sphere.center.Z, 1);

        auto m = GetMatrix();

        h = m.Multiply(h);
        c = m.Multiply(c);
        
        sphere.center = Vector3(c.X, c.Y, c.Z);
        sphere.radius = sphere.center.distance(h);
    }
    
private:
    Vector3 getPush(const float& ts)
    {
        Push += (Translation - PreviousTranslation) * ts;
        return Push *= Drag;
    }
    
    Vector3 getSpin(const float& ts)
    {
        Spin += (Rotation - PreviousRotation) * ts;
        return Spin *= Drag;
    }
};


#endif /* Transform_hpp */
