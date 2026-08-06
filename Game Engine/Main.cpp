#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <fmod.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random> 

using namespace nu;
using namespace std;


class Object {
public:
    Object() { cout << "constructor\n"; }
	~Object() { cout << "destructor\n"; }

	Object(const Object& object) { cout << "copy constructor\n"; }
	Object& operator = (const Object& object) { cout << "copy assignment\n"; return *this; }
};


uint32_t seed = 1234;

uint32_t RNG() {
    seed = (seed * 1103515245) + 12345;
    return seed;
}


int main(){

 //   //rand()
 //   for (size_t i = 0; i < 10; i++) { cout << RNG() << " "; }
	//cout << endl;
	//seed = 1234;
 //   for (size_t i = 0; i < 10; i++) { cout << RNG() << " "; }
 //   cout << endl;

 //   //srand((unsigned int)time(NULL));
	//SeedRandom((unsigned int)time(NULL));
 //   for (size_t i = 0; i < 10; i++) { cout << rand() << " "; }
 //   cout << endl;

 //   //<random>
	//random_device rd;
	//cout << "random_device min: " << rd.min() << " " << endl;
	//cout << "random_device max: " << rd.max() << " " << endl;
	//cout << "random_device entropy: " << rd.entropy() << " " << endl;
	////Mersenne Twister
	//mt19937 generator(rd());
	//uniform_int_distribution<> dist(0, 20);
 //   for (size_t i = 0; i < 10; i++) { cout << dist(generator) << " "; }
 //   cout << endl;
 //   uniform_real_distribution<float> distReal(-10.0f, 20.0f);
 //   for (size_t i = 0; i < 10; i++) { cout << distReal(generator) << " "; }
 //   cout << endl;
 //   return 0;
	//cout << "==============Object==============\n";
 //   {
 //       Object objectA;
	//	Object objectB = objectA; // copy constructor
	//	Object objectC;
	//	objectC = objectA; // copy assignment 
 //   }

 //   cout << "\n==============Raw_Pointers==============\n";
 //   {
	//	Object* objectA = new Object();
	//	cout << "objectA address: " << objectA << endl;

	//	Object* objectB = new Object(*objectA); // copy constructor
 //       cout << "objectB address: " << objectB << endl;

 //       Object* objectC = nullptr;
 //       objectC = objectA;
 //       cout << "objectC address: " << objectC << endl;

 //       delete objectA;
 //       delete objectB;
 //       //delete objectC;
 //   }

 //   cout << "\n==============Unique_Pointers==============\n";
 //   {
	//	unique_ptr<Object> objectA = make_unique<Object>();
 //       cout << "objectA address: " << objectA.get()<< endl;

 //       unique_ptr<Object> objectB;
	//	objectB = move(objectA); // move constructor
 //       cout << "objectB address: " << objectB.get() << endl;

	//	objectB.reset(); // delete objectB
 //   }

 //   cout << "\n==============Shared_Pointers==============\n"; 
	//shared_ptr<Object> objectC;
 //   {
	//	auto objectA = make_shared<Object>();
 //       cout << "objectA address: " << objectA.get() << endl;
	//	cout << objectA.use_count() << endl;
	//	auto objectB = objectA; // copy constructor
 //       cout << "objectB address: " << objectB.get() << endl;
 //       cout << objectB.use_count() << endl;
 //       objectC = objectA;
 //       cout << "objectC address: " << objectC.get() << endl;
 //       cout << objectC.use_count() << endl;
 //   }
 //   cout << objectC.use_count() << endl;

	////return 0;


    SetWorkingDirectory("Assets");

    //INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
   
	shared_ptr<Texture> texture = make_shared<Texture>();
	//texture->Load("Textures/player.png", Engine::Get().GetRenderer());

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
        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("Textures/player.png", Engine::Get().GetRenderer()), 30, 30, 45.0f);
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    
    }
    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}