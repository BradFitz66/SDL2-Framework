#include <stdio.h>
#include "SDL_image.h"
#include <cassert>
#include <string>
#include "Framework/Game.hpp"
#include "Framework/Sprite.hpp"
#include "Framework/Input.hpp"
struct Player{
	Sprite* texture;
	float x, y;
};

class TestGame : public Game
{
public:
	TestGame(int tick_interval = 60) : Game(tick_interval){
		show_demo_window = new bool(true);
	}
	void Update(double dt)
	{
		//Set the window title to the delta time
		//Convert DT(milliseconds) to FPS
		float fps = 1 / (dt / 1000);
		SDL_SetWindowTitle(window, std::to_string(fps).c_str());
		float vertical = input->GetValue("Vertical");
		float horizontal = input->GetValue("Horizontal");
		
		player->x += horizontal * 128 * dt;
		player->y += vertical * 128 * dt;
		
		if(input->GetValue("ChangeSprite") && change_sprite_timer > change_sprite_time)
		{
			player->texture->SetIndex((player->texture->GetIndex() + 1) % 10);
			change_sprite_timer = 0;
		}
		change_sprite_timer += dt;
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
		player->texture = new Sprite(0, 5, 10, 10, 32, 32, "SpriteSheetTest.png", renderer);
		player->x = 0;
		player->y = 0;
		
		input = InputManager::GetSingleton();

		input->AddAxis("Vertical", SDL_SCANCODE_S, SDL_SCANCODE_W);
		input->AddAxis("Horizontal", SDL_SCANCODE_D, SDL_SCANCODE_A);
		input->AddButton("ChangeSprite", SDL_SCANCODE_SPACE);
	}
private:
	bool* show_demo_window;
	Player* player;
	InputManager* input;
	float change_sprite_timer = 0;
	float change_sprite_time = 0.5f;
};

int main(int argc,char** argv)
{
	TestGame* game = new TestGame();
	game->Run();
	delete game;
	return 0;
}
