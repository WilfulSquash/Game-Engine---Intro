#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>

using namespace nu;
using namespace std;


class Object {
public:
    Object() { cout << "constructor\n"; }
	~Object() { cout << "destructor\n"; }

	Object(const Object& object) { cout << "copy constructor\n"; }
	Object& operator = (const Object& object) { cout << "copy assignment\n"; return *this; }
};


int main(){

	cout << "==============Object==============\n";
    {
        Object objectA;
		Object objectB = objectA; // copy constructor
		Object objectC;
		objectC = objectA; // copy assignment 
    }

    cout << "\n==============Raw_Pointers==============\n";
    {
		Object* objectA = new Object();
		cout << "objectA address: " << objectA << endl;

		Object* objectB = new Object(*objectA); // copy constructor
        cout << "objectB address: " << objectB << endl;

        Object* objectC = nullptr;
        objectC = objectA;
        cout << "objectC address: " << objectC << endl;

        delete objectA;
        delete objectB;
        //delete objectC;
    }

    cout << "\n==============Smart_Pointers==============\n";
    {
		unique_ptr<Object> objectA = make_unique<Object>();
        cout << "objectA address: " << objectA.get()<< endl;

        unique_ptr<Object> objectB;
		objectB = move(objectA); // move constructor
        cout << "objectB address: " << objectB.get() << endl;

		objectB.reset(); // delete objectB
    }

	//return 0;


    SetWorkingDirectory("Assets");

    //INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
   
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
        
        game.Update(Engine::Get().GetTime().GetDeltaTime());

        //RENDER
        Engine::Get().GetRenderer().SetColorf(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();
		
        game.Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    
    }
    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}