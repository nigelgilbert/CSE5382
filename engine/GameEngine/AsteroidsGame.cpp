//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.

#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>

#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"

using namespace std;

AsteroidsGame::AsteroidsGame() : ShaderFolder("Shaders/")
{
    deathCount = 0;
    lastLazerFire = 0;
}

bool AsteroidsGame::OnCreateScene()
{
    myShip = &CreateShip();
    for (int i = 0; i < 5; i++)
    {
        auto asteroid = &CreateAsteroid();
        myAsteroids.push_back(asteroid);
    }
    
    for (int i = 0; i < 3; i++)
    {
        auto ship = &CreateHP();
        ship->Transform.Translation = Vector3(6 + (i*1.5), 7, 0);
        HP.push_back(ship);
    }
    
    auto& cam = Game::Camera;
    cam.Transform.Translation.Z = 20;
    cam.BuildFrustumPlane();
    return true;
}

void AsteroidsGame::CheckCollisions(const GameTime& time)
{
    auto shipBounds = myShip->bounds;
    for (auto asteroid : myAsteroids)
    {
        if (asteroid->bounds.intersects(shipBounds))
        {
            deathCount += 1;
            if (deathCount == 3)
            {
                StartNewGame();
            }
            for (int i = 0; i < deathCount; ++i)
            {
                HP[i]->Transform.Translation = Vector3(100,0,0);
            }
                
            myShip->reset();
            std::cout << "collision @ frame #" << time.FrameNumber() << std::endl;
        }
        
        for (auto lazer: firedLazers)
        {
            if (asteroid->bounds.intersects(lazer->bounds))
            {
                destroyedAsteroids.push_back(asteroid);
                asteroid->destroy();
                if (destroyedAsteroids.size() == myAsteroids.size())
                    StartNewLevel();
            }
        }
    }
}

void AsteroidsGame::StartNewLevel()
{
    for (auto asteroid : destroyedAsteroids)
    {
        asteroid->spawn();
    }
    
    for (int i = 0; i < 2; i++)
    {
        auto asteroid = &CreateAsteroid();
        asteroid->Initialize();
        myAsteroids.push_back(asteroid);
    }
    
    destroyedAsteroids.clear();
}

void AsteroidsGame::StartNewGame()
{
    for (auto asteroid : myAsteroids)
    {
        asteroid->spawn();
    }
    
    deathCount = 0;
    for (int i = 0; i < 3; i++)
    {
        HP[i]->Transform.Translation = Vector3(6 + (i*1.5), 7, 0);
    }
    
}

void AsteroidsGame::OnPreRender(const GameTime& time)
{
    if (glfwGetKey(Window(), GLFW_KEY_F) == GLFW_PRESS)
    {
        ThrottleFireLazer(time);
    }
    
    CheckCollisions(time);
}

void AsteroidsGame::onLazerCull()
{
    if (!recycledLazers.empty())
    {
        Lazer* lazer = firedLazers.back();
        firedLazers.pop_back();
        recycledLazers.push_back(lazer);
        std::cout << "lazer recycled" << std::endl;
    }
}

void AsteroidsGame::ThrottleFireLazer(const GameTime& time)
{
    if (time.TotalSeconds() - lastLazerFire > .5)
    {
        lastLazerFire = time.TotalSeconds();
        CreateLazer();
    }
    else if (lastLazerFire == 0)
    {
        lastLazerFire = time.TotalSeconds();
        CreateLazer();
    }
}

Lazer& AsteroidsGame::CreateLazer()
{
    if (!recycledLazers.empty())
    {
        Lazer* lazer = recycledLazers.front();
        recycledLazers.pop_front();
        lazer->spawn(myShip->Transform.Translation, myShip->Transform.Rotation);
        return *lazer;
    }
    else
    {
        auto& lazer = Create<Lazer>("lazer");
        lazer.Initialize();
        lazer.spawn(myShip->Transform.Translation, myShip->Transform.Rotation);
        lazer.setCullCallback(this);
        firedLazers.push_front(&lazer);
        return lazer;
    }
}

Ship& AsteroidsGame::CreateShip()
{
    auto& ship = Create<Ship>("ship");
    return ship;
}


HPShip& AsteroidsGame::CreateHP()
{
    auto& hp = Create<HPShip>("hp");
    return hp;
}

Asteroid& AsteroidsGame::CreateAsteroid()
{
    auto& asteroid = Create<Asteroid>("asteroid");
    return asteroid;
}