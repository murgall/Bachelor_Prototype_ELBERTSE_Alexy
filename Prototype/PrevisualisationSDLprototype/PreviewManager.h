#pragma once
#ifndef __PreviewManager__
#define __PreviewManager__

#include <SDL.h>
#include<SDL_image.h>



class PreviewManager
{

private:
	static PreviewManager* pr_pInstance;

	SDL_Window *pr_pWindow;
	SDL_Renderer *pr_pRenderer;





	int pr_gameWidth;
	int pr_gameHeight;
public:
	/*PreviewManager();
	~PreviewManager();*/
	// create the public instance function
	static PreviewManager* Instance();
	int init(const char *title, int xpos, int ypos, int height, int width, int flags);
	void render();
	void clean();
	void quit();

	SDL_Renderer* getRenderer() const;



	int getGameWidth() const
	{
		return pr_gameWidth;
	}

	int getGameHeight() const
	{
		return pr_gameHeight;
	}
};

typedef PreviewManager ThePrevisualisation;





#endif 