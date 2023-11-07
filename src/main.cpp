#include <stdio.h>
#include "SDL_image.h"
#include <cassert>
#include <string>
#include "Framework/Game.hpp"
#include "Framework/Input.hpp"
#include "Framework/Tilemap.hpp"


class TestGame : public Game
{
public:
	TestGame(int tick_interval = 60) : Game(tick_interval)
	{
	}
	void Update(double dt)
	{
	}

	void Render()
	{
		tilemap->Render(this->renderer);
	}

	void HandleEvents(SDL_Event event, ImGuiIO &io)
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			quit = true;
		}
		// Get mouse input
		case SDL_MOUSEBUTTONDOWN:
		{
			// Check if mouse is over any imgui window
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			break;
		}
		case SDL_MOUSEMOTION:
		{
			break;
		}

		break;
		}
	}

	void Clean()
	{
	}

	void Load()
	{
		input = InputManager::GetSingleton();
		input->AddButton("Clear Screen", SDL_SCANCODE_C);
		input->AddButton("Quit", SDL_SCANCODE_ESCAPE);
		tilemap = new Tilemap("res/maps/Classroom.tmx",renderer);
	}

private:
	InputManager *input;
	Tilemap *tilemap;
};

// Force dedicated GPU on Nvidia Optimus
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(int argc, char **argv)
{

	TestGame *game = new TestGame();
	game->Run();
	//If we get here, the game loop has ended. Wait until the user presses enter in the console window.
	delete game;
	printf("Press enter key to exit.\n");
	getchar();
	return 0;
}
