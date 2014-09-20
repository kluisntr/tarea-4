#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include <iostream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;

int tile_width = 64;

bool puedoLLegar(int tablero[5][5],
            int x_inicial, int y_inicial,
            int x_destino, int y_destino,
            int pasos)
{
     if(x_inicial>=5 || x_inicial<0 || y_inicial>=5 || y_inicial<0)
        return false;
    if(tablero[y_inicial][x_inicial]==1)
        return false;
    if(tablero[y_destino][x_destino]==1)
        return false;
    if(tablero[y_inicial][x_inicial]==2)
        pasos-=1;
    if(x_destino>=5 || x_destino<0 || y_destino>=5 || y_destino<0)
        return false;
    if(x_inicial==x_destino && y_inicial==y_destino)
        return true;
    if(pasos<=0)
        return false;
    bool puedo_der = puedoLLegar(tablero,
        x_inicial+1,y_inicial,
        x_destino,y_destino,pasos-1);
    bool puedo_izq = puedoLLegar(tablero,
        x_inicial-1,y_inicial,
        x_destino,y_destino,
        pasos-1);
    bool puedo_arriba = puedoLLegar(tablero,
        x_inicial,y_inicial-1,
        x_destino,y_destino,
        pasos-1);
    bool puedo_abajo = puedoLLegar(tablero,
        x_inicial,y_inicial+1,
        x_destino,y_destino,
        pasos-1);
    return puedo_der || puedo_izq || puedo_arriba || puedo_abajo;



}

int main()
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Este es mi mensaje", 100, 100, 800/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    SDL_Texture *texture_piso, *texture_pared;
    SDL_Texture *texture_mago;
    SDL_Texture *texture_cursor;
    SDL_Texture *texture_seleccionado;
    SDL_Rect rectangulo;
    texture_piso = IMG_LoadTexture(renderer,"piso.png");
    texture_pared = IMG_LoadTexture(renderer,"pared.png");
    texture_mago = IMG_LoadTexture(renderer,"mago.png");
    texture_cursor = IMG_LoadTexture(renderer,"cursor.png");
    texture_seleccionado = IMG_LoadTexture(renderer,"seleccionado.png");

    rectangulo.h = tile_width;
    rectangulo.w = tile_width;

    int arr[5][5]= {{0,1,1,0,0},
                    {0,1,0,0,0},
                    {0,1,1,0,1},
                    {0,1,2,0,1},
                    {0,0,0,1,1}};
        cout<<puedoLLegar(arr,0,0,2,1,15)<<endl;
bool estado=false;
    int frame = 0;
    int frame_anterior = 0;
    int cursor_x = 0;
    int cursor_y = 0;

    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_w)
                {
                    cursor_y--;
                }
                if(Event.key.keysym.sym == SDLK_a)
                {
                    cursor_x--;
                }
                if(Event.key.keysym.sym == SDLK_s)
                {
                    cursor_y++;
                }
                if(Event.key.keysym.sym == SDLK_d)
                {
                    cursor_x++;
                }

            }
        }
        for(int x=0;x<5;x++)
        {
            for(int y=0;y<5;y++)
            {
                if(arr[y][x]==1)
                {
                    rectangulo.x = x*tile_width;
                    rectangulo.y = y*tile_width;
                    SDL_RenderCopy(renderer, texture_pared, NULL, &rectangulo);
                }
                else
                {
                    rectangulo.x = x*tile_width;
                    rectangulo.y = y*tile_width;
                    SDL_RenderCopy(renderer, texture_piso, NULL, &rectangulo);
                }
            }
        }


        if (puedoLLegar(arr,0,0,2,1,20))
        {
        rectangulo.x =  tile_width*2;
        rectangulo.y = tile_width*1;
        SDL_RenderCopy(renderer, texture_mago, NULL, &rectangulo);
        }

        rectangulo.x = 0;
        rectangulo.y = 0;
        SDL_RenderCopy(renderer, texture_mago, NULL, &rectangulo);

        rectangulo.x = cursor_x*tile_width;
        rectangulo.y = cursor_y*tile_width;
        SDL_RenderCopy(renderer, texture_cursor, NULL, &rectangulo);

        SDL_RenderPresent(renderer);

        frame++;
        int frame_actual = SDL_GetTicks() - frame_anterior;
        frame_anterior = SDL_GetTicks();
        if(17-frame_actual>0)
            SDL_Delay( 17-frame_actual );
    }

    cout << "Hello world!" << endl;
    return 0;
}
