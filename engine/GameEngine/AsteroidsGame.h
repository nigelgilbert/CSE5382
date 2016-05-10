//
//  SimpleGame.hpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H

#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "hp.h"
#include "Lazer.h"
#include <list>
#include <vector>
class AsteroidsGame : public Game
{
public:
    AsteroidsGame();
    
    void CheckCollisions(const GameTime& time);
    void StartNewLevel();
    void StartNewGame();
    
    bool OnCreateScene() override;
    void OnPreRender(const GameTime& time) override;
    
    void ThrottleFireLazer(const GameTime& time);
    void onLazerCull() override;

    /// location of shaders in the file system.
	std::string ShaderFolder;
    
    Ship& CreateShip();
    HPShip& CreateHP();
    Lazer& CreateLazer();
    Asteroid& CreateAsteroid();
    
private:
    int deathCount;
    float lastLazerFire;
    std::list<Lazer*> firedLazers;
    std::list<Lazer*> recycledLazers;
    
    std::list<Asteroid*> myAsteroids;
    std::list<Asteroid*> destroyedAsteroids;
    
    std::vector<HPShip*> HP;
    Ship* myShip;
};


#endif /* SimpleGame_hpp */
