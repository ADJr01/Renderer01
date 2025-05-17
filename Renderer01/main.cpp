#include<iostream>
#include<SDL.h>
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool is_created = false;
bool init_sdl();

int main(int argc,char* args[]) {
	is_created = init_sdl();
	if (!is_created)
	{
		std::cerr << "Failed to initialize SDL system."<<SDL_GetError() << std::endl;
		return 1;
	}
	std::cout<<"Initialized SDL"<<std::endl;
	return 0;
}

bool init_sdl() {
	if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
		std::cerr<<"Failed To Initialize SDL"<<std::endl;
		return false;
	}
	//creating sdl window
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1080,
		768,
		SDL_WINDOW_BORDERLESS
		);
	if (!window)
	{
		std::cerr<<"Failed To Create Window"<<std::endl;
		return false;
	}
	//create sdl renderer
	renderer = SDL_CreateRenderer(
		window,
		-1,
		0 
		);
	if (!renderer)
	{
		std::cerr<<"Failed To Create Renderer"<<std::endl;
		return false;
	}
	return true;
}