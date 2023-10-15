#pragma once
#include <SDL.h>
#include <iostream>
#include "Input.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL_opengl.h>
//Class that contains the game loop and the main functions
class Game
{
public:
    Game(int tick_interval = 60, bool use_imgui = false) : tick_interval(tick_interval) {}

    virtual void Update(float dt)=0;
    virtual void Render()=0;
    virtual void HandleEvents(SDL_Event event)=0;
    virtual void Clean()=0;
    virtual void Load()=0;

    void Run()
    {
        //Initialize SDL
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
            	std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	 
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    	SDL_DisplayMode current;
   	SDL_GetCurrentDisplayMode(0, &current);
	
	//Create window
        window = SDL_CreateWindow(
			"SDL Tutorial", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			640, 
			480, 
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
        if(window == NULL)
            	std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    	
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	
	IMGUI_CHECKVERSION();
    	ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    	ImGui::StyleColorsDark();
    	
    	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    	ImGui_ImplOpenGL3_Init("#version 130");
	
        //Create renderer for window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;

        Load();
        //Calculate delta time
        Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	dt = 0.0f;
	bool show_demo_window = true;
	while(!quit)
	{
		LAST = NOW;
		if(SDL_PollEvent(&event))
	    	{
			
			ImGui_ImplSDL2_ProcessEvent(&event);
			HandleEvents(event);
			//Update axis and buttons
			if(event.type==SDL_KEYDOWN || event.type==SDL_KEYUP){
				//Convert the event to a keyboard event
				SDL_KeyboardEvent event_keyboard = event.key;
				InputManager::GetSingleton()->Update(event_keyboard);
			}

		}
	
	    			    
            	//Update
            	Update(dt);
        
	
			
		NOW = SDL_GetPerformanceCounter();
	    	dt = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		
		//Render
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		
		//Show imgui demo window
		ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		Render();

		//Render draw data
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);				
				
	    	//Calculate delta time

        }
        Clean();
    }
    ~Game()
    {
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

