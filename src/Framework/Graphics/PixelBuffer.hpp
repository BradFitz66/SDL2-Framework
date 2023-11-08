#ifndef PIXELBUFFER_HPP
#define PIXELBUFFER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "../Miscellaneous/IRenderable.hpp"

class PixelBuffer : public IRenderable
{
public:
	PixelBuffer(int width, int height, SDL_Rect* dest, SDL_Renderer* renderer )
	: width(width), height(height), renderer(renderer)
	{
		pixels = new uint32_t[width * height];
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		src = new SDL_Rect{
			0,
			0,
			width,
			height
		};

		this->dest = dest;
	}

	~PixelBuffer()
	{
		delete[] pixels;
	}

	void SetPixel(int x, int y, uint32_t color)
	{
		//Make sure we are in bounds
		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		pixels[y * width + x] = color;
		dirty = true;
	}
	
	

	uint32_t GetPixel(int x, int y)
	{
		return pixels[y * width + x];
	}

	void Clear(uint32_t color)
	{
		for (int i = 0; i < width * height; i++)
			pixels[i] = color;

		dirty = true;
	}

	void Render(SDL_Renderer* renderer)
	{
		if (dirty)
		{
			UpdateTexture();
			dirty = false;
		}
		SDL_RenderCopy(renderer, texture, NULL, dest);


	}

private:
	uint32_t* pixels;
	int width;
	int height;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect* src;
	SDL_Rect* dest;
	bool dirty = false;

	void UpdateTexture()
	{
		int32_t pitch = 0;	
		if(!SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch))
		{
			pitch /= sizeof(uint32_t);
			SDL_UnlockTexture(texture);
		}
		else{
			printf("Error locking texture: %s\n", SDL_GetError());
		}
	}
};
#endif