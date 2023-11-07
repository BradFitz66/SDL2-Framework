//Class for handling input
#ifndef INPUT_HPP
#define INPUT_HPP
#include <map>
#include "SDL.h"
#include <stdexcept>
#include <functional>
class Input{
public:
	void Set(int value){
		this->value = value;
	}
	int Get(){
		return value;
	}
	virtual void Update()=0;
protected:
	float value;
};

class Axis : public Input{
public:
	Axis(SDL_Scancode positive, SDL_Scancode negative){
		this->positive = positive;
		this->negative = negative;
	}
	void Update(){
		int negative = SDL_GetKeyboardState(NULL)[this->negative]!=0 ? 1 : 0;
		int positive = SDL_GetKeyboardState(NULL)[this->positive]!=0 ? 1 : 0;	
		value = positive - negative;

	}
private:
	SDL_Scancode positive, negative;
};

class Button : public Input{
public:
	Button(SDL_Scancode button){
		this->button = button;
	}
	void Update(){
		value = SDL_GetKeyboardState(NULL)[button] ? 1 : 0;

	}
private:
	SDL_Scancode button;
};

class InputManager{
public:
	static InputManager* GetSingleton(){
		static InputManager* instance = nullptr;
		if(instance==nullptr)
			instance = new InputManager();
		return instance;
	}
	void Update(SDL_KeyboardEvent event){
		if(actions.find(event.keysym.scancode)!=actions.end())
			actions[event.keysym.scancode]();
	
	}
	void AddAxis(std::string name, SDL_Scancode positive, SDL_Scancode negative){
		if(inputs.find(name)!=inputs.end())
			throw std::runtime_error("Axis already exists");
		inputs[name] = new Axis(positive, negative);
		//Create the lambda for updating the axis
		actions[positive] = [this, name](){
			inputs[name]->Update();
		};	
		actions[negative] = [this, name](){
			inputs[name]->Update();
		};
	}
	void AddButton(std::string name, SDL_Scancode button){
		if(inputs.find(name)!=inputs.end())
			throw std::runtime_error("Button already exists");
		inputs[name] = new Button(button);
		actions[button] = [this, name](){
			inputs[name]->Update();
		};
	}
	float GetValue(std::string name){
		if(inputs.find(name)==inputs.end())
			throw std::runtime_error("Input does not exist");
		return inputs[name]->Get();
	}
protected:
	//Map storing all of the lambdas for updating axis and buttons. Key is the scan code with the value being the lambda
	std::map<SDL_Scancode, std::function<void()>> actions;
	std::map<std::string, Input*> inputs;
};
#endif