#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Graphics/Transform.hpp"
#include "../Miscellaneous/IRenderable.hpp"

#include <vector.h>
#include <SDL.h>

#include <vector>

class Camera : public Transform
{
    public:
    //Constructor
    Camera(vector2D<float> position, vector2D<float>  scale) : Transform(position, rotation, scale){}

    
    //Camera render function takes  a vector of objects that inherit from IRenderable 
    void Render(SDL_Renderer* renderer, std::vector<IRenderable*> renderables)
    {
        //Loop through all renderables
        for (int i = 0; i < renderables.size(); i++)
        {
            //Render the object
            renderables[i]->Render(renderer, position.x, position.y);
        }
    }

};

#endif