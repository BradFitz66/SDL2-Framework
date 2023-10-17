#include <SDL.h>
#include <iostream>
int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return -1;

  std::cout << "hello\n";
  std::cin.get();

  SDL_Quit();

  return 0;
}
