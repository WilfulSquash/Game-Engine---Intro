#include "../Engine/Engine.h"
#include "SpaceGame/Player.h"
#include "SpaceGame/Enemy.h"
#include "SpaceGame/Bullet.h"
#include "SpaceGame/Assets.h"
#include "SpaceGame/SpaceGame.h"
#include "SpriteGame/SpriteGame.h"

#include <fmod.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random> 
#include <fstream>

using namespace nu;
using namespace std;

int main(){
    //DON'T F***ING TOUCH THIS
    SetWorkingDirectory("Assets");
    
    //INITIALIZATION
    Engine::Get().Initialize();

    unique_ptr<Game> game = make_unique<SpriteGame>();
    game->Initialize();
   
	shared_ptr<Texture> texture = make_shared<Texture>();

    //UPDATE
    bool quit = false;
    while (!quit) {
        
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        //Engine
        Engine::Get().Update();
        
        game->Update(Engine::Get().GetTime().GetDeltaTime());

        //RENDER
        Engine::Get().GetRenderer().SetColorf(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();
		
        game->Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    
    }
    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}