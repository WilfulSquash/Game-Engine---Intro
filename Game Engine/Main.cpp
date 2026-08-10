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
#include <fstream>

using namespace nu;
using namespace std;


int main(){

    SetWorkingDirectory("Assets");

    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/json.txt", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (nu::Load("data/json.txt", document))
        {
            // read/show the data from the json file
            std::string name;
            int age;
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
    }

     /*   //Read file (input file)
        ifstream file("data/test.txt");
     {
        if (file.is_open()) {
            string str;
            while (getline(file, str)) {
			    cout << str << endl;
            }
		}
		else { cout << "Failed to open file" << endl; }
        file.close();
    }

    {
        //Read file (output file)
        ofstream file("data/test.txt", ios::app);
        if (file.is_open()) {
            file << "Testing More\n";
        }
    }

    {
        //Read / Write (input/output)
        fstream file("data/test.txt", ios::in | ios::out | ios::app);
        if (file.is_open()) {
            //input
            file << "Add a line\n";
            file.seekg(0);
            //output
            string str;
            while (getline(file, str)) {
                cout << str << endl;
            }
        }
    }

    {
        string name;
        int score;
        bool isAlive;

        //save game data
        bool save = false;
        if (save == true) {
			name = "Player1";
			score = 100;
			isAlive = true;

            //save game data
            ofstream file("data/game.txt");
            if (file.is_open()) {
                file << name << "\n";
                file << score << "\n";
				file << boolalpha << isAlive << "\n";
            }
        }

        //load game data
        bool load = true;
        if (load == true) {
            //read file
            ifstream file("data/game.txt");
            if (file.is_open()) {
                getline(file, name);

                string str;
                getline(file, str);

                score = stoi(str);

                //file >> score;
                file >>boolalpha >> isAlive;
            }
        }
        //display game data
        cout << name << endl;
        cout << score << endl;
        cout << boolalpha << isAlive << endl;
    }

    return 0;*/

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
		//Puts Player ship in top left corner of screen
        //Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("Textures/player.png", Engine::Get().GetRenderer()), 30, 30, 45.0f);
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    
    }
    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}