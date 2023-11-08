//Include guard
#ifndef TEXTURE_HPP
#define TEXTURE_HPP


//Texture class for drawing images  
#include <cassert>
#include <string>
#include <SDL_image.h>

class Texture
{
public:
    Texture(SDL_Renderer* renderer, std::string path, int width=0, int height=0, bool auto_size=false)
    {
        //Load image at specified path
        SDL_Surface* loaded_surface = IMG_Load(path.c_str());

        if(loaded_surface == NULL)
            throw std::runtime_error(SDL_GetError());

        //If auto_size is true, set width and height to the width and height of the loaded surface
        if(auto_size)
        {
            width = loaded_surface->w;
            height = loaded_surface->h;
        }

        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(texture == NULL)
            throw std::runtime_error(SDL_GetError());
        
        //Get rid of old loaded surface
        SDL_FreeSurface(loaded_surface);

        
    }

    //Copy constructor
    Texture(const Texture& other)
    {
        texture = other.texture;
        width = other.width;
        height = other.height;
    }

    //Move constructor
    Texture(Texture&& other)
    {
        texture = other.texture;
        width = other.width;
        height = other.height;
        other.texture = NULL;
    }


    ~Texture()
    {
        //Free texture if it exists
        if(texture != NULL)
            SDL_DestroyTexture(texture);
    }
    
    //Overload for converting Texture to an SDL_Texture* (return the texture pointer)
    operator SDL_Texture*()
    {
        return texture;
    }

    void Render(SDL_Renderer* renderer, int x, int y)
    {
        if(texture == NULL)
            throw std::runtime_error("Texture is NULL");
        //Set rendering space and render to screen
        SDL_Rect render_quad = {x, y, width, height};

        if(SDL_RenderCopy(renderer, texture, NULL, &render_quad) != 0)
            throw std::runtime_error(SDL_GetError());
    }
    
    void Render(SDL_Renderer* renderer, int x, int y,  double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        if(texture == NULL)
            throw std::runtime_error("Texture is NULL");

        //Set rendering space and render to screen
        SDL_Rect render_quad = {x, y, width, height};

        if(SDL_RenderCopyEx(renderer, texture, NULL, &render_quad, angle, center, flip) != 0)
            throw std::runtime_error(SDL_GetError());
    }

    void Render(SDL_Renderer* renderer, SDL_Rect* src_rect, SDL_Rect* dst_rect)
    {        
        if(SDL_RenderCopy(renderer, texture, src_rect, dst_rect) != 0)
            throw std::runtime_error(SDL_GetError());
    }

    int GetWidth()
    {
        return width;
    }

    int GetHeight()
    {
        return height;
    }

protected:
    SDL_Texture* texture;
    int width, height;

};

#endif