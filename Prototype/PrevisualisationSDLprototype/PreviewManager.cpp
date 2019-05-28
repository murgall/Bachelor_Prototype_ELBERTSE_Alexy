#include <iostream>
#include "PreviewManager.h"
#include "TextureManager.h"






PreviewManager * PreviewManager::Instance()
{
	if (pr_pInstance == 0)
	{
		pr_pInstance = new PreviewManager();
		return pr_pInstance;
	}
	return pr_pInstance;
}

PreviewManager* PreviewManager::pr_pInstance = 0;


int PreviewManager::init(const char * title, int xpos, int ypos, int height, int width, int flags)
{
	pr_gameHeight = height;
	pr_gameWidth = width;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		//if succeeded create our window
		pr_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		//if succeeded create window, create our render
		if (pr_pWindow != NULL) {
			std::cout << "window creation success\n";
			pr_pRenderer = SDL_CreateRenderer(pr_pWindow, -1, SDL_RENDERER_ACCELERATED);
			if (pr_pRenderer != NULL) {

				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(pr_pRenderer, 0, 0, 0, 255);
				SDL_RenderClear(pr_pRenderer);//clear the render to the draw color

				int flags = IMG_INIT_JPG | IMG_INIT_PNG;
				int initted = IMG_Init(flags);
				if ((initted&flags) != flags) {

					std::cerr << "IMG_Init: Failed to init required jpg and png support!\n";
					std::cerr << "IMG_Init:" << IMG_GetError();
					SDL_Delay(5000);
					return 0;

					// handle error
				}
			}
			else {
				//si la valeur du render est NULL (ne se charge pas)
				std::cerr << "Failed to init renderer!\n";
				std::cerr << "Error" << SDL_GetError();
				SDL_Delay(5000);
				return 0;
			}


		}
		else {
			//si la valeur de la fenêtre est NULL (ne se charge pas)
			std::cerr << "Failed to init window!\n";
			std::cerr << "Error" << SDL_GetError();
			SDL_Delay(5000);
			return 0;
		}


	}
	else {
		//si la SDL2 ne se charge pas
		std::cerr << "Fail to init SDL2\n";
		std::cerr << "Error" << SDL_GetError();
		SDL_Delay(5000);
		return 0;
	}

	std::cout << "init success\n";
	return 1;
}

void PreviewManager::render()
{
	//SDL_RenderClear(pr_pRenderer); // clean le render


	SDL_RenderPresent(pr_pRenderer); // dessine le render à l'écran


}





SDL_Renderer * PreviewManager::getRenderer() const
{
	return pr_pRenderer;
}



void PreviewManager::clean()
{
	std::cout << "cleaning previsualisation\n";
	SDL_DestroyWindow(pr_pWindow);
	SDL_DestroyRenderer(pr_pRenderer);
	SDL_Quit();
}

void PreviewManager::quit()
{
	SDL_Quit();
}
