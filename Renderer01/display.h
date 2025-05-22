#ifndef DISPLAY_H
#define DISPLAY_H
#include<SDL.h>
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;
//?Flags
extern uint32_t* Color_Buffer;

//screen config
extern uint64_t WIDTH;
extern uint64_t HEIGHT;

bool init_sdl();
void update();
void clear_color_buffer();
void render();
void render_color_buffer();
bool draw_rectangle(int x,int y,int width,int height);
bool draw_triangle(int max_dots);
void destroy_window();
#endif