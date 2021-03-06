//
//  Camera.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Game.h"
#include "Camera.h"
#include "Vectors.h"
#include "math.h"

void Camera::BuildFrustumPlane() {
    
    int w, h;
    Game::GetFramebufferSize(&w, &h);
    float aspect = w * 1.f / h;
    
    // find the half spaces [OFF THE BLOG]
    float halfheight = tan(FieldOfView / 2);
    float halfwidth = halfheight * aspect;
    
    // get the points
    Vector3 a(-halfwidth, halfheight, 1);
    Vector3 b(halfwidth, halfheight, 1);
    Vector3 c(halfwidth, -halfheight, 1);
    Vector3 d(-halfwidth, -halfheight, 1);
    
    // get the normals
    topNorm = a.cross(b).normalize();
    rightNorm = b.cross(c).normalize();
    botNorm = c.cross(d).normalize();
    leftNorm = d.cross(a).normalize();
}

Matrix& Camera::GetProjectionMatrix()
{
    /// check aspect
    int w, h;
    
    Game::GetFramebufferSize(&w, &h);
    
    float aspect = w * 1.f / h;
    
    if (aspect != m_previousAspectRatio)
    {
        m_projectionMatrix = Matrix::CreatePerspective(FieldOfView, aspect, ZNear, ZFar);
        m_previousAspectRatio = aspect;
    }
    
    return m_projectionMatrix;
}

Matrix& Camera::GetViewMatrix()
{
    auto t = Transform.Translation * -1.f;
    auto r = Transform.Rotation * -1.f;
    
    m_viewMatrix = Matrix::CreateRotation(r) * Matrix::CreateTranslation(t);
    
    return m_viewMatrix;
    
}

