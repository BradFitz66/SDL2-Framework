#include <stdio.h>
#include "SDL_image.h"
#include <cassert>
#include <string>
#include "Framework/Game.hpp"
#include "Framework/Texture.hpp"
#include "Framework/Input.hpp"
struct Player{
	Texture* texture;
	float x, y;
};

class TestGame : public Game
{
public:
	TestGame(int tick_interval = 60) : Game(tick_interval){
		show_demo_window = new bool(true);
	}
	void Update(float dt)
	{
		//Set the window title to the delta time
		SDL_SetWindowTitle(window, std::to_string(dt).c_str());	
		float vertical = input->GetValue("Vertical")/4;
		float horizontal = input->GetValue("Horizontal")/4;
		printf("%f %f\n", vertical, horizontal);
		player->x += horizontal * dt;
		player->y += vertical * dt;
	}
	
	void Render()
	{
		player->texture->Render(renderer, player->x, player->y);
	}

	void HandleEvents(SDL_Event event)
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				quit = true;
			}
			break;
		}
		
	}

	void Clean()
	{
		
	}

	void Load()
	{
		player = new Player();
		player->texture = new Texture(renderer, "Square.png", 25,25);
		player->x = 0;
		player->y = 0;
		
		input = InputManager::GetSingleton();

		input->AddAxis("Vertical", SDL_SCANCODE_S, SDL_SCANCODE_W);
		input->AddAxis("Horizontal", SDL_SCANCODE_D, SDL_SCANCODE_A);
	}
private:
	bool* show_demo_window;
	Player* player;
	InputManager* input;
};

int main(int argc,char** argv)
{
	TestGame* game = new TestGame();
	game->Run();
	delete game;
	return 0;
}
