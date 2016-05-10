//
//  Ship.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "Ship.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

bool Ship::OnInitialize()
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

void Ship::OnUpdate(const GameTime& time)
{
    wrap();
    
    Transform.setPrevious();
    auto timeScale = Transform.getTimeScale(time);
    
    if (glfwGetKey(game->Window(), GLFW_KEY_UP) == GLFW_PRESS)
        Transform.moveUp(.09);
    
    if (glfwGetKey(game->Window(), GLFW_KEY_DOWN) == GLFW_PRESS)
        Transform.moveUp(-.09);
    
    if (glfwGetKey(game->Window(), GLFW_KEY_LEFT) == GLFW_PRESS)
        Transform.moveYaw(-.1);
    
    if (glfwGetKey(game->Window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        Transform.moveYaw(.1);

    Transform.Verlet(timeScale);
    bounds.center = Transform.Translation;
}


void Ship::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();

    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
  
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

void Ship::reset()
{
    Transform.reset();
}

void Ship::wrap()
{
    Vector3 pos = (Transform.Translation - Game::Camera.Transform.Translation);
    
    if (pos.dot(Game::Camera.topNorm) < 0)
        Transform.Translation.Y *= - 1;
    
    if (pos.dot(Game::Camera.leftNorm) < 0)
        Transform.Translation.X *= - 1;
    
    if (pos.dot(Game::Camera.botNorm) < 0)
        Transform.Translation.Y *= - 1;
    
    if (pos.dot(Game::Camera.rightNorm) < 0)
        Transform.Translation.X *= - 1;
}

