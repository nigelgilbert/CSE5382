//
//  lazer.cpp
//  GameEngine
//
//  Created by Nigel Gilbert on 5/8/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "lazer.h"

Lazer::Lazer()
{
    isCulled = true;
    parent = nullptr;
}

bool Lazer::OnInitialize()
{
    vector<Vector3> vertices =
    {
        Vector3(0, 0.4f, 0),
        Vector3(1/10.f, 0, 0),
        Vector3(-1/10.f, 0, 0)
    };
    
    vector<GLushort> indices = {0,1,2};
    
    auto& mesh = Create<Mesh>("lazer-mesh");
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    game = &Game::Instance();
    
    auto& material = Create<class Material>("lazer-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    bounds.initialize(vertices);
    Transform.scaleSphere(bounds);
    
    return material.Build("Shaders/primitive");
}

void Lazer::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

void Lazer::OnUpdate(const GameTime& time)
{
    cull();
    Transform.setPrevious();
    Transform.moveUp(.3);
    bounds.center = Transform.Translation;
}

bool Lazer::isOutOfScreen()
{
    Vector3 pos = (Transform.Translation - Game::Camera.Transform.Translation);

    if (pos.dot(Game::Camera.topNorm) < 0)
        return true;
    
    if (pos.dot(Game::Camera.leftNorm) < 0)
        return true;
    
    if (pos.dot(Game::Camera.botNorm) < 0)
        return true;
    
    if (pos.dot(Game::Camera.rightNorm) < 0)
        return true;
    
    return false;
}

void Lazer::setCullCallback(Game *g)
{
    parent = g;
}

void Lazer::cull()
{
    if (isOutOfScreen())
    {
        isCulled = true;
        if (parent != nullptr)
            parent->onLazerCull();
    }
}

void Lazer::spawn(Vector3 translation, Vector3 rotation)
{
    Transform.Translation = translation;
    Transform.Rotation = rotation;
}
