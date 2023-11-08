#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <SDL.h>
#include <vector.h>
//Transform class for storing position, rotation and scale for objects
class Transform
{
    public:
    //Constructor
    Transform(vector2D<float> position, float rotation, vector2D<float>  scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    //Copy constructor
    Transform(const Transform& other)
    {
        position = other.position;
        rotation = other.rotation;
        scale = other.scale;
    }

    //Move constructor
    Transform(Transform&& other)
    {
        position = other.position;
        rotation = other.rotation;
        scale = other.scale;
        other.position = vector2D<float>(0,0);
        other.rotation = 0;
        other.scale = vector2D<float>(0,0);
    }

    //Getters
    vector2D<float> GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    vector2D<float> GetScale() const { return scale; }

    //Setters
    void SetPosition(vector2D<float> position) { this->position = position; }
    void SetRotation(float rotation) { this->rotation = rotation; }
    void SetScale(vector2D<float> scale) { this->scale = scale; }


    protected:
    vector2D<float>  position;
    float rotation;
    vector2D<float>  scale;

};

#endif