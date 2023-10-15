//Texture class for drawing images  
#include <cassert>
#include <string>
#include "SDL_image.h"

class Texture
{
public:
    Texture(SDL_Renderer* renderer, std::string path, int width, int height) : width(width), height(height)
    {
        //Load image at specified path
        SDL_Surface* loaded_surface = IMG_Load(path.c_str());
        assert(loaded_surface != NULL);

        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        assert(texture != NULL);

        //Get rid of old loaded surface
        SDL_FreeSurface(loaded_surface);
    }

    ~Texture()
    {
        //Free texture if it exists
        if(texture != NULL)
            SDL_DestroyTexture(texture);
    }

    void Render(SDL_Renderer* renderer, int x, int y)
    {
        //Set rendering space and render to screen
        SDL_Rect render_quad = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, NULL, &render_quad);
    }
    
    void Render(SDL_Renderer* renderer, int x, int y,  double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        //Set rendering space and render to screen
        SDL_Rect render_quad = {x, y, width, height};
        SDL_RenderCopyEx(renderer, texture, NULL, &render_quad, angle, center, flip);
    }

    int GetWidth()
    {
        return width;
    }

    int GetHeight()
    {
        return height;
    }

private:
    SDL_Texture* texture;
    int width, height;

};