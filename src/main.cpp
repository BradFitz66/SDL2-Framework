#include <stdio.h>
#include "SDL_image.h"
#include <cassert>
#include <string>
#include "Framework/Game.hpp"
#include "Framework/Sprite.hpp"
#include "Framework/Input.hpp"
#include "Framework/PixelBuffer.hpp"
struct Player{
	Sprite* texture;
	float x, y;
};

class TestGame : public Game
{
public:
	TestGame(int tick_interval = 60) : Game(tick_interval){	
	}
	void Update(double dt)
	{
		
		//Set the window title to the delta time
		//Convert DT(milliseconds) to FPS
		float fps = 1 / (dt);
		SDL_SetWindowTitle(window, std::to_string(fps).c_str());

		if (mouseDown)
		{
			Paint(mouseX, mouseY);	
		}
	}
	
	void Render()
	{
		//Set clear color
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect* dest = new SDL_Rect();
		dest->x = 0;
		dest->y = 0;
		dest->w = 640;
		dest->h = 480;


		buffer->Render(dest);
	}
	
	void Paint(int x, int y)
	{
		//Use dda to draw a line from the last mouse position to the current one
		int dx,dy,steps,k;
		float xinc,yinc,x2,y2;
		dx=x-mouseLastX;
		dy=y-mouseLastY;

		if(abs(dx)>abs(dy))
			steps=abs(dx);
		else
			steps=abs(dy);

		xinc=(float)dx/(float)steps;
		yinc=(float)dy/(float)steps;

		x2=mouseLastX;
		y2=mouseLastY;

		for(k=0;k<steps;k++)
		{
			x2+=xinc;
			y2+=yinc;
			//Set the pixel at the current mouse position to a random color
			int pixelX = (int)x2 / pixelSize;
			int pixelY = (int)y2 / pixelSize;
	

			buffer->SetPixel(pixelX, pixelY, ARGB(255,0,0,255));
		}

	}


	void HandleEvents(SDL_Event event, ImGuiIO& io)
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				quit = true;
			}
			//Get mouse input
			case SDL_MOUSEBUTTONDOWN:
			{
				//Check if mouse is over any imgui window
				if (event.button.button == SDL_BUTTON_LEFT && !io.WantCaptureMouse)
				{
					mouseDown = true;
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				if (event.button.button == SDL_BUTTON_LEFT )
				{
					mouseDown = false;
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				mouseLastX = mouseX;
				mouseLastY = mouseY;
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				break;
			}

			break;
		}
		
	}

	uint32_t ARGB(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
	{
		return (a << 24) | (r << 16) | (g << 8) | b;
	}
	
	inline uint32_t FastRand(void) 
	{   
			uint32_t t;

			sRandX ^= sRandX << 16;
			sRandX ^= sRandX >> 5;
			sRandX ^= sRandX << 1;

			t = sRandX;
			sRandX = sRandY;
			sRandY = sRandZ;
			sRandZ = t ^ sRandX ^ sRandY;

			return sRandZ;
	}


	void Clean()
	{

	}

	void Load()
	{
		//Scaled width is window size / pixel size
		scaledWidth = 640 / pixelSize;
		scaledHeight = 480 / pixelSize;
		buffer = new PixelBuffer(scaledWidth, scaledHeight, renderer);
		buffer->Clear(0xFF000000);
	}
private:
	PixelBuffer* buffer;

	uint32_t pixelSize = 4;

	uint32_t sRandX = 123456789;
	uint32_t sRandY = 362436069;
	uint32_t sRandZ = 521288629;
	
	int scaledWidth;
	int scaledHeight;

	bool mouseDown = false;
	int mouseX, mouseY;
	int mouseLastX, mouseLastY;
};

//Force dedicated GPU on Nvidia Optimus
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(int argc,char** argv)
{

	TestGame* game = new TestGame();
	game->Run();
	delete game;
	return 0;
}
