#include<iostream>
#include<SDL.h>
#include "display.h"
bool SDL_INIT_FLAG = false; // Runtime Flag
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* color_buffer_texture = nullptr;
uint32_t* Color_Buffer = nullptr;
//screen config
uint64_t WIDTH = 800;
uint64_t HEIGHT = 600;
//?Flags

// function declarations
void setup();
void process_input();
int tick();




int main(int argc,char* args[]) {
	SDL_INIT_FLAG = init_sdl();
	if (!SDL_INIT_FLAG)
	{
		std::cerr << "Failed to initialize SDL system."<<SDL_GetError() <<"\n";
		return 1;
	}
	std::cout<<"Initialized SDL"<<"\n";
	setup();
	return tick();
}



void setup(){
	const size_t n = WIDTH * HEIGHT;
	Color_Buffer = new(std::nothrow) uint32_t[n];
	if (!Color_Buffer ){
		std::cerr<<"Failed To Setup Color Buffer\n";
		throw std::runtime_error("Failed To Setup Color Buffer");
	}
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT
		);
	if (color_buffer_texture==nullptr ){
		std::cerr<<"Failed To Setup Color Buffer Texture"<<std::endl;
		throw std::runtime_error("Failed To Setup Color Buffer Texture");
	}
	std::cout<<"Setup Complete"<<std::endl;

	return;
}
int tick(){
	try
	{
		while (SDL_INIT_FLAG){
			process_input();
			update();
			render();
		}
		destroy_window();
		return 0;
	}catch (...)
	{
		std::cerr<<"Runtime Error"<<std::endl;
		destroy_window();
		return 1;
	}
}
void process_input(){
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT){
		SDL_INIT_FLAG = false;
	}else if (event.type == SDL_KEYDOWN){
		 const auto key = event.key.keysym.sym;
		if (key==SDLK_ESCAPE){
			SDL_INIT_FLAG = false;
		}
	}
}





