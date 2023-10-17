#pragma once

#include <SDL.h>
#include <SDL_image.h>

class PixelBuffer
{
public:
	PixelBuffer(int width, int height, SDL_Renderer* renderer)
	: width(width), height(height), renderer(renderer)
	{
		pixels = new uint32_t[width * height];
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		src = new SDL_Rect();
		src->x = 0;
		src->y = 0;
		src->w = width;
		src->h = height;
	}

	~PixelBuffer()
	{
		delete[] pixels;
	}

	void SetPixel(int x, int y, uint32_t color)
	{
		pixels[y * width + x] = color;
		UpdateTexture();
	}
	
	

	uint32_t GetPixel(int x, int y)
	{
		return pixels[y * width + x];
	}

	void Clear(uint32_t color)
	{
		for (int i = 0; i < width * height; i++)
			pixels[i] = color;
		UpdateTexture();
	}

	void Render(SDL_Rect* dest)
	{
		SDL_RenderCopy(renderer, texture, NULL, dest);
	}

private:
	uint32_t* pixels;
	int width;
	int height;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect* src;

	void UpdateTexture()
	{
		int32_t pitch = 0;

		if(!SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch))
		{
			pitch /= sizeof(uint32_t);
			SDL_UnlockTexture(texture);
		}

	}
};
