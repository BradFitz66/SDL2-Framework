#pragma once
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <chrono>

#include "Input.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

struct Clock{
	uint32_t last_tick_time = 0;
	uint32_t delta = 0;
	void Tick(){
		uint32_t current_time = SDL_GetTicks();
		delta = current_time - last_tick_time;
		last_tick_time = current_time;
	}
};

// Class that contains the game loop and the main functions
class Game {
public:
	Game(int tick_interval = 60, bool use_imgui = false)
	: tick_interval(tick_interval) {}

	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(SDL_Event event) = 0;
	virtual void Clean() = 0;
	virtual void Load() = 0;

	void Run() {
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()<< std::endl;

		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		SDL_DisplayMode current;
		SDL_GetCurrentDisplayMode(0, &current);

		// Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
															640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
						);
		if (window == NULL)
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;

		SDL_GLContext gl_context = SDL_GL_CreateContext(window);
		SDL_GL_SetSwapInterval(1);	// Enable vsync

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init("#version 130");

		// Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
			std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		
		//SDL enable vsync
		//SDL_RenderSetVSync(renderer,1);

		Load();
		// Calculate delta time using std::chrono
		Uint32 last = SDL_GetPerformanceCounter();
		Uint32 now = SDL_GetPerformanceCounter();
		dt = 0.0f;
		bool show_demo_window = true;
		Clock clock = Clock();
		while (!quit) {
			last = now;
			now = SDL_GetPerformanceCounter();
			dt = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
			if (SDL_PollEvent(&event)) {
				ImGui_ImplSDL2_ProcessEvent(&event);
				HandleEvents(event);
				// Update axis and buttons
				if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
					// Convert the event to a keyboard event
					SDL_KeyboardEvent event_keyboard = event.key;
					InputManager::GetSingleton()->Update(event_keyboard);
				}
			}
			printf("Delta: %d\n", clock.delta);
			// Update
			Update(dt / 1000);
					

			// Render
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(window);
			ImGui::NewFrame();	
			
			// Show imgui demo window
			ImGui::ShowDemoWindow(&show_demo_window);
			 
			ImGui::Render();
			glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
			glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
			glClear(GL_COLOR_BUFFER_BIT);
			 
			Render();
			 
			// Render draw data
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			SDL_GL_SwapWindow(window);
		
			// Calculate delta time
			} 
			Clean();	
		}

		~Game() {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
			 
			SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
 
protected:
	bool quit = false;
	double tick_interval;
	double dt = 0.0f;
	SDL_Event event;
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
};

