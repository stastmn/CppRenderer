// Renderer.cpp : Определяет точку входа для приложения.
//only x64 build

#include "framework.h"
#include "Renderer.h"
#include <iostream>
#include <SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_targetTexture = nullptr;

void g_InitSdlResourses();
void g_FreeSdlResourses();

int main(int argc, char * argv[])
{

	g_InitSdlResourses();

	//render texture
/*	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, g_targetTexture, NULL, NULL);
	SDL_RenderPresent(g_renderer);
	SDL_Delay(4000);*/

	//drawing

	Uint32* pixels = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];
	Uint32* middle = &pixels[WINDOW_WIDTH * 240];
	for(int i = 0;i<WINDOW_WIDTH;i++)
	{
		Uint8* c =(Uint8*) &middle[i];
		c[2] = 255;
	}

	
	SDL_UpdateTexture(g_targetTexture, NULL, pixels, sizeof(Uint32) * WINDOW_WIDTH);
	
	
	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, g_targetTexture, NULL, NULL);
	SDL_RenderPresent(g_renderer);
	SDL_Delay(4000);

	delete[] pixels;
	g_FreeSdlResourses();
	std::cin.get();
	return 0;
}

void g_InitSdlResourses()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}
	else
	{
		std::cout << "SDL initialization succeeded!" << std::endl;
	}


	g_window = SDL_CreateWindow("Renderer", 100, 100,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == nullptr)
	{
		std::cout << "SDL window creating failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}


	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer == nullptr)
	{
		std::cout << "SDL renderer creating failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}

	g_targetTexture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (g_targetTexture == nullptr)
	{
		std::cout << "SDL texture creating failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}
}

void g_FreeSdlResourses()
{
	//cleanup
	if (g_targetTexture != nullptr) {
		SDL_DestroyTexture(g_targetTexture);
		g_targetTexture = nullptr;
	}
	if (g_renderer != nullptr)
	{
		SDL_DestroyRenderer(g_renderer);
		g_renderer = nullptr;
	}
	if (g_window != nullptr)
	{
		SDL_DestroyWindow(g_window);
		g_window = nullptr;
	}
	SDL_Quit();
	
}
