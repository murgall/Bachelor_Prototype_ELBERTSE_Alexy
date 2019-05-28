#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	//Si l'image ne se charge pas
	if (pTempSurface == 0)
	{
		std::cerr << "IMG_Load returned NULL for " << id << ", from : " << fileName << "\n";

		std::cerr << "IMG_Load error : " << SDL_GetError() << "\n";
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);
	//std::cout << pTexture << "\n";

	if (pTexture != 0)
	{
		//charge la texture map avec le tileset, permettant de dessiner avec.
		m_textureMap[id] = pTexture;
		return true;
	}

	std::cout << "can't load texturmanager"<<"\n";

	// reaching here means something went wrong
	return false;
}

/*void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}*/

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}

void TextureManager::drawTile(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;//l� o� se trouve le tileset
	SDL_Rect destRect;//la position souhait�e dans le render

	srcRect.x = width * currentRow;
	srcRect.y = height * currentFrame;

	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);//dessine la tile
}