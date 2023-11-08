//Interface for renderable objects (implementing the render function)

#ifndef IRENDERABLE_HPP
#define IRENDERABLE_HPP

#include <SDL.h>

class IRenderable
{
    public:
    //Inheriting object MUST implement this function
    virtual void Render(SDL_Renderer* renderer, int xOffset=0, int yOffset=0) = 0;
};

#endif