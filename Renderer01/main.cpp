#include<iostream>
#include<SDL.h>
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool SDL_INIT_FLAG = false;
// function declarations
bool init_sdl();
void setup();
void process_input();
void update();
void render();
void cleanup();

int main(int argc,char* args[]) {
	SDL_INIT_FLAG = init_sdl();
	if (!SDL_INIT_FLAG)
	{
		std::cerr << "Failed to initialize SDL system."<<SDL_GetError() << std::endl;
		return 1;
	}
	std::cout<<"Initialized SDL"<<std::endl;
	setup();
	while (SDL_INIT_FLAG){
		process_input();
		//if (!SDL_INIT_FLAG)return 0;
		update();
		render();
	}
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
void setup(){}
void process_input()
{
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
void update(){

}
void render(){
	SDL_SetRenderDrawColor(renderer,105,195,125,190);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}