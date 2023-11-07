#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <iostream>
#include "Texture.hpp"

//Renders a sprite from a spritesheet
class Sprite : public Texture
{
public:
	Sprite(
		int index,
		int sprites_per_row,
		int sprite_width,
		int sprite_height,
		int width,
		int height,
		std::string texture_path,
		SDL_Renderer* renderer
	) : Texture(renderer, texture_path, width, height)
	{
		this->index = index;
		this->sprites_per_row = sprites_per_row;
		this->sprite_width = sprite_width;
		this->sprite_height = sprite_height;
		this->width = width;
		this->height = height;

		src_rect.x = (index % sprites_per_row) * sprite_width;
		src_rect.y = (index / sprites_per_row) * sprite_height;
		src_rect.w = sprite_width;
		src_rect.h = sprite_height;

		dst_rect.w = width;
		dst_rect.h = height;
	}
	

	/// <summary>
	/// Renders the sprite
	/// </summary>
	/// <param name="renderer">The SDL renderer</param>
	/// <param name="x">The x position of the sprite</param>
	/// <param name="y">The y position of the sprite</param>
	/// <returns></returns>
	void Render(SDL_Renderer* renderer, int x, int y)
	{
		//Use the render function from the Texture class
		dst_rect.x = x;
		dst_rect.y = y;
		Texture::Render(renderer, src_rect, dst_rect);
	}

	/// <summary>
	/// Sets the index of the sprite in the spritesheet
	/// </summary>
	/// <param name="index">The index of the sprite in the spritesheet</param>
	/// <returns></returns>
	void SetIndex(int index)
	{
		this->index = index;
		src_rect.x = (index % sprites_per_row) * sprite_width;
		src_rect.y = (index / sprites_per_row) * sprite_height;
	}

	/// <summary>
	/// Gets the index of the sprite in the spritesheet
	/// </summary>
	/// <returns>The index of the sprite in the spritesheet</returns>
	/// <returns></returns>
	int GetIndex()
	{
		return index;
	}
private:
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	int index; //Index of the sprite in the spritesheet
	int sprites_per_row;
	int sprite_width, sprite_height;
	int width, height; //Width and height of the sprite in the world
};

#endif