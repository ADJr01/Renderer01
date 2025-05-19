#include<iostream>
#include<SDL.h>
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* color_buffer_texture = nullptr;
//?Flags
bool SDL_INIT_FLAG = false; // Runtime Flag
uint32_t* Color_Buffer = nullptr;

// function declarations
bool init_sdl();
void setup();
void process_input();
void update();
void clear_color_buffer();
void render();
void render_color_buffer();
void cleanup();
int gameLoop();
void destroy_window();

//screen config
const uint16_t WIDTH = 800;
const uint16_t HEIGHT = 600;

//static colors 0xFF00EE09
static uint32_t RED = 0xFFFF0000;
static uint32_t GREEN = 0xFF00FF00;
static uint32_t BLUE = 0xFF0000FF;


int main(int argc,char* args[]) {
	SDL_INIT_FLAG = init_sdl();
	if (!SDL_INIT_FLAG)
	{
		std::cerr << "Failed to initialize SDL system."<<SDL_GetError() << std::endl;
		return 1;
	}
	std::cout<<"Initialized SDL"<<std::endl;
	setup();
	
	return gameLoop();
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
		WIDTH,
		HEIGHT,
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
		SDL_DestroyWindow(window);
		std::cerr<<"Failed To Create Renderer"<<std::endl;
		return false;
	}
	return true;
}
void setup(){
	const size_t n = WIDTH * HEIGHT;
	Color_Buffer = new(std::nothrow) uint32_t[n];
	if (!Color_Buffer ){
		std::cerr<<"Failed To Setup Color Buffer"<<std::endl;
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
int gameLoop(){
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
void update(){
	//TODO:
}
void clear_color_buffer(){
	auto set_color_buffer = [](size_t index,uint32_t color_hex)->void{
		Color_Buffer[index] = color_hex;
	};
	for (int y = 0; y < HEIGHT; y++){
		for (int x = 0; x < WIDTH; x++){
			set_color_buffer((WIDTH*y)+x,GREEN);
		}
	}
}
void render_color_buffer(){
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		Color_Buffer,
		(sizeof(uint32_t) * WIDTH)
		);
	SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}
void render(){
	SDL_SetRenderDrawColor(renderer,105,195,125,190);
	SDL_RenderClear(renderer);
	render_color_buffer();
	clear_color_buffer();
	SDL_RenderPresent(renderer);
}
void destroy_window()
{
	delete[] Color_Buffer;
	Color_Buffer = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}