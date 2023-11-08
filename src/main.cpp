#include <SDL_image.h>
#include <stdio.h>
#include <cassert>
#include <string>

#include "Framework/Core/Game.hpp"
#include "Framework/IO/Input.hpp"
#include "Framework/Graphics/Tilemap.hpp"
#include "Framework/Miscellaneous/Camera.hpp"



class TestGame : public Game
{
public:
	TestGame(int tick_interval = 60) : Game(tick_interval)
	{
	}
	void Update(double dt)
	{
		//Set title to show FPS
		std::string title = "SDL Framework - FPS: " + std::to_string(1.0 / dt);

		vector2D<float> movement = vector2D<float>(input->GetValue("Horizontal"), input->GetValue("Vertical")) * 100.0f * dt;
		camera->SetPosition(camera->GetPosition() + movement);

		SDL_SetWindowTitle(window, title.c_str());

		//Handle input
		if (input->GetValue("Quit"))
		{
			quit = true;
		}
	}

	void Render()
	{
		camera->Render(renderer, {tilemap});
	}

	void HandleEvents(SDL_Event event, ImGuiIO &io)
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			printf("Quit\n");
			quit = true;
			break;
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
		input->AddAxis("Scroll", SDL_SCANCODE_Q, SDL_SCANCODE_E);
		input->AddAxis("Horizontal", SDL_SCANCODE_A, SDL_SCANCODE_D);
		input->AddAxis("Vertical", SDL_SCANCODE_W, SDL_SCANCODE_S);

		tilemap = new Tilemap("res/maps/Classroom.tmx",renderer);
		camera = new Camera(vector2D<float>(0,0),vector2D<float>(1,1));
	}

private:
	InputManager *input;
	Tilemap *tilemap;
	Camera *camera;
	float zoom = 1.0f;
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
	delete game;
	return 0;
}
