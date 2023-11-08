#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <iostream>

#include "Texture.hpp"
#include "Transform.hpp"
#include "../Miscellaneous/IRenderable.hpp"

//Renders a sprite from a spritesheet
class Sprite : public Texture, public Transform, public IRenderable
{
public:
	Sprite(
		int indexX,
		int indexY,
		int sprite_width,
		int sprite_height,
		int width,
		int height,
		std::string texture_path,
		SDL_Renderer* renderer
	) : Texture(renderer, texture_path, width, height), Transform(vector2D<float>(0, 0), 0, vector2D<float>(width, height))
	{
		this->indexX = indexX;
		this->indexY = indexY;
		this->sprite_width = sprite_width;
		this->sprite_height = sprite_height;
		this->width = width;
		this->height = height;

		src_rect = new SDL_Rect{
			//Calculate x and y position of the sprite in the spritesheet
			indexX * sprite_width,
			indexY * sprite_height,
			sprite_width,
			sprite_height
		};

		dst_rect = new SDL_Rect{
			0,
			0,
			width,
			height
		};		
	}
	

	/// <summary>
	/// Renders the sprite
	/// </summary>
	/// <param name="renderer">The SDL renderer</param>
	/// <param name="x">The x position of the sprite</param>
	/// <param name="y">The y position of the sprite</param>
	/// <returns></returns>
	void Render(SDL_Renderer* renderer, int xOffset=0, int yOffset=0) override
	{
		//Use the render function from the Texture class
		dst_rect->x = xOffset + GetPosition().x;
		dst_rect->y = yOffset + GetPosition().y;
		Texture::Render(renderer, src_rect, dst_rect);
	}

	/// <summary>
	/// Sets the index of the sprite in the spritesheet
	/// </summary>
	/// <param name="index">The index of the sprite in the spritesheet</param>
	/// <returns></returns>
	void SetIndex(int indexX, int indexY)
	{
		this->indexX = indexX;
		this->indexY = indexY;
	}

	/// <summary>
	/// Gets the column index of the sprite in the spritesheet
	/// </summary>
	/// <returns>The column index of the sprite in the spritesheet</returns>
	/// <returns></returns>
	int GetIndexX()
	{
		return indexX;
	}

	/// <summary>
	/// Gets the row index of the sprite in the spritesheet
	/// </summary>
	/// <returns>The row index of the sprite in the spritesheet</returns>
	/// <returns></returns>
	int GetIndexY()
	{
		return indexY;
	}
private:
	SDL_Rect* src_rect;
	SDL_Rect* dst_rect;
	int indexX; //Index of the sprite in the spritesheet
	int indexY;
	int sprite_width, sprite_height;
	int width, height; //Width and height of the sprite in the world
};

#endif