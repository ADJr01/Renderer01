#include "display.h"

#include <cstdint>
#include <iostream>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <__msvc_ostream.hpp>

bool init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cerr<<"Failed To Initialize SDL"<<std::endl;
        return false;
    }
    //query window width and height
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0,&display_mode);
    WIDTH = display_mode.w;
    HEIGHT = display_mode.h;
    //creating sdl window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        static_cast<int>(WIDTH),
        static_cast<int>(HEIGHT),
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
    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    return true;
}
void update(){
    //TODO:
}
void clear_color_buffer(){
    auto set_color_buffer = [](size_t index,uint32_t color_hex)->void{
        Color_Buffer[index] = color_hex;
    };
    for (int row = 0; row < HEIGHT; row++){ //each row
        for (int cell = 0; cell < WIDTH; cell++){ //each column
            set_color_buffer((WIDTH*row)+cell,0xFF333333);
		 
        }
    }
}
void render(){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    draw_triangle(400);
    render_color_buffer();
    clear_color_buffer();
    SDL_RenderPresent(renderer);
}
void render_color_buffer(){
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        Color_Buffer,
        static_cast<int>(sizeof(uint32_t) * WIDTH)
        );
    SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}
bool draw_rectangle(int x,int y,int width,int height){
    try{
        auto set_color_buffer = [](size_t index,uint32_t color_hex)->void{
            Color_Buffer[index] = color_hex;
        };
        if (x>WIDTH || y> HEIGHT || (x+width)>WIDTH || (y+height)>HEIGHT)return false;
        const int rect_height = y+height;
        const int rect_width = x+width;
        for (int row = y;row<rect_height;row++)
        {
            for (int cell = x;cell<rect_width;cell++)
            {
                set_color_buffer((WIDTH*row)+cell,0xFFFF00FF);
            }
        }
        return true;
    }
    catch (...)
    {
        std::cerr<<"Runtime Error"<<std::endl;
        return false;
    }
}
void destroy_window()
{
    delete[] Color_Buffer;
    Color_Buffer = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
bool draw_triangle(int max_dots){
    int total_dots_painted = max_dots;
    for (int row = max_dots;row>0;row--)
    {
        for (int cell = 0;cell<max_dots;cell++)
        {
            const auto cel_to_paint = (WIDTH*row) + cell;
            if (!(cell < (max_dots-total_dots_painted) || cell > total_dots_painted))
            {
                Color_Buffer[cel_to_paint]=0xFFFFFFFF;
            }
        }
        total_dots_painted--;
    }
    return true;
}