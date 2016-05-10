//
//  HP.cpp
//  GameEngine
//
//  Created by Nigel Gilbert on 5/9/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "HP.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

using namespace std;

bool HPShip::OnInitialize()
{
    auto& mesh = Create<Mesh>("ship-mesh");
    /// narrow triangle pointed along the positive Y axis
    vector<Vector3> vertices =
    {
        Vector3(0, 0.5f, 0),
        Vector3(1/3.f, -0.5f, 0),
        Vector3(-1/3.f, -0.5f, 0)
    };
    
    vector<GLushort> indices = {0,1,2};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    game = &Game::Instance();
    
    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    bounds.initialize(vertices);
    Transform.scaleSphere(bounds);
    
    std::cout << "Ship bounding sphere initialized:" << this->bounds.radius << std::endl;
    
    return material.Build("Shaders/primitive");
}

void HPShip::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}