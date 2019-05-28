#include <iostream>
#include "PreviewManager.h"
#include "TextureManager.h"
#include "tinyxml.h"


using namespace std;



int main(int argc, char * argv[])
{
	//variable correspondant à la balise <map>
	int m_tileWidth;
	int m_tileHeight;
	int m_width;
	int m_height;


	//variable correspondant à la balise <tileset> et <image>
	string tls_name;
	int tls_tileWidth;
	int tls_tileHeight;
	int tls_tileCount;
	int tls_columns;

	string img_source = "assets/";
	int img_width;
	int img_height;

	//variable correspondant à la balise <layer> et <tile>
	int lay_firstGid;
	string lay_name;
	int lay_width;
	int lay_height;

	int tile_id;
	int tile_x;
	int tile_y;
	int numero_col;
	int numero_ligne;



	//crée le DOM xml auquel on pourra récupérer les valeurs dont on aura besoin
	TiXmlDocument levelDocument;
	levelDocument.LoadFile("assets/test.xml");

	//récupere la node racine, ici le <map>
	TiXmlElement* pRoot = levelDocument.RootElement();

	//récupération des attribut de <map>
	pRoot->Attribute("tilewidth", &m_tileWidth);
	pRoot->Attribute("tileheight", &m_tileHeight);


	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	//permet de set les variables pour la dimension de la fenêtre que l'on va créer
	int widthWindow = m_tileWidth*m_width;
	int heightWindow = m_tileHeight*m_height;

	//cout << levelDocument.GetDocument()->Value() << "\n";
	cout << "previsualisation init attempt...\n";


	if (ThePrevisualisation::Instance()->init("previsualisation", 100, 100,heightWindow ,widthWindow , false))
	{



		//parcourt les nodes enfants de <map>
		for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			//si la node sélectionnée correspond à la node <tileset>
			if (e->Value() == string("tileset"))
			{
				//récupère le nom du tileset ainsi que la source de l'image
				tls_name = e->Attribute("name");
				img_source = img_source+e->FirstChildElement()->Attribute("source");

				cout << img_source << "\n";

				//ajout du tileset dans le texture manager
				TheTextureManager::Instance()->load(img_source, tls_name, ThePrevisualisation::Instance()->getRenderer());


				//récupération des attribut de <tileset> et <image>
				e->Attribute("tilewidth", &tls_tileWidth);
				e->Attribute("tileheight", &tls_tileHeight);
				e->Attribute("tilecount", &tls_tileCount);
				e->Attribute("columns", &tls_columns);

				e->FirstChildElement()->Attribute("width", &img_width);
				e->FirstChildElement()->Attribute("height", &img_height);
			}
		}




		//reparcourt les nodes enfants de <map>
		for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			//si la node sélectionnée correspond à la node <layer>
			if(e->Value() == string("layer"))
			{
				e->Attribute("firstgid", &lay_firstGid);
				e->Attribute("width", &lay_width);
				e->Attribute("height", &lay_height);


				//parcours chaque tile du <layer> sélectionné
				for (TiXmlElement* e2 = e->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
				{
					e2->Attribute("id", &tile_id);
					
					e2->Attribute("x", &tile_x);
					e2->Attribute("y", &tile_y);





					
					if (tile_id > -1) 
					{
						numero_col = tile_id / tls_columns;
						numero_ligne = tile_id - numero_col * tls_columns;
						//dessine le tile dans le render
						TheTextureManager::Instance()->drawTile(tls_name,tile_x,tile_y,tls_tileWidth,tls_tileHeight,numero_col,numero_ligne, ThePrevisualisation::Instance()->getRenderer());
						//vérifie les attributs des tiles
						cout << "Id de la tile : "<< tile_id << "\n";
						cout << "position x de la tile : " << tile_x << "\n";
						cout << "position y de la tile : " << tile_y << "\n";
						cout << "colonne  de la tile : " << numero_col << "\n";
						cout << "ligne de la tile : " << numero_ligne << "\n";
						cout << "\n";
					}

				}
			}
		}



		cout << "previsualisation init success!\n";	
		ThePrevisualisation::Instance()->render();

		SDL_Delay(5000);
	}

	else

	{
		cout << "previsualisation init failure - " << SDL_GetError() << "\n";

		return -1;
	}

	cout << "previsualisation closing...\n";

	ThePrevisualisation::Instance()->clean();

	return 0;
}