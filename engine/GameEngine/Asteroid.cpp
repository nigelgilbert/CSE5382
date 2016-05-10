//
//  Asteroid.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Asteroid.h"
#include <vector>

using namespace std;

bool Asteroid::OnInitialize()
{
    float X = 0.525731112119133606f;
    float Z = 0.850650808352039932f;
    
    vector<Vector3> vertices =
    {
        Vector3(-X, 0.f, Z),
        Vector3(X, 0.f, Z),
        Vector3(-X, 0.f, -Z),
        Vector3(X, 0.f, -Z),
        Vector3(0.f, Z, X),
        Vector3(0.f, Z, -X),
        Vector3(0.f, -Z, X),
        Vector3(0.f, -Z, -X),
        Vector3(Z, X, 0.f),
        Vector3(-Z, X, 0.f),
        Vector3(Z, -X, 0.f),
        Vector3(-Z, -X, 0.f)
    };
    
    vector<GLushort> indices =
    {
        0, 4, 1,
        0, 9, 4,
        9, 5, 4,
        4, 5, 8,
        4, 8, 1,
        8, 10, 1,
        8, 3, 10,
        5, 3, 8,
        5, 2, 3,
        2, 7, 3,
        7, 10, 3,
        7, 6, 10,
        7, 11, 6,
        11, 0, 6,
        0, 1, 6,
        6, 1, 10,
        9, 0, 11,
        9, 11, 2,
        9, 2, 5,
        7, 2, 11
    };
    
    auto& mesh = Create<Mesh>("asteroid-mesh");
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    game = &Game::Instance();
    
    // TODO: rename asteroid material
    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    spawn();
    
    bounds.initialize(vertices);
    Transform.scaleSphere(bounds);

    return material.Build("Shaders/primitive");
}

void Asteroid::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

void Asteroid::OnUpdate(const GameTime& time)
{
    wrap();
    Transform.setPrevious();
    Transform.moveUp(.09);
    Transform.Translation.Z *= -.1;
    bounds.center = Transform.Translation;
}

void Asteroid::wrap()
{
    Vector3 pos = (Transform.Translation - Game::Camera.Transform.Translation);
    
    if (pos.dot(Game::Camera.topNorm) < 0)
    {
        Transform.Translation.Y *= - 1;
    }
    
    if (pos.dot(Game::Camera.leftNorm) < 0)
    {
        Transform.Translation.X *= - 1;
    }
    
    if (pos.dot(Game::Camera.botNorm) < 0)
    {
        Transform.Translation.Y *= - 1;
    }
    
    if (pos.dot(Game::Camera.rightNorm) < 0)
    {
        Transform.Translation.X *= - 1;
    }
}

void Asteroid::spawn()
{
    Transform.Rotation.Z += (rand() % 100) / 100.f;
    Transform.Rotation.X += (rand() % 100) / 100.f;
    Transform.Translation = Vector3(rand() % 15, rand() % 10, rand() % 15);
}

void Asteroid::destroy()
{
    Transform.Rotation = Vector3(0,0,0);
    Transform.Translation = Vector3(-100,0,0);
}