#include "Core.h"

using namespace core;

Engine::Engine()
{



	//TO DO:
	//
	//shaderManager = nullptr;
	//bufferManager = nullptr;
	//textureManager = nullptr;
	//spriteManager = nullptr;
	//textManager = nullptr;
	//audioManager = nullptr;
}


Engine::~Engine()
{

}

void Engine::Init()
{

	
	//SDL Init()
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		fprintf_s(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());		
	}	

	//Glew Init()
	//glewExperimental = GL_TRUE;

	glewInit();

	//freetype init()
	//
	//Do we even want this here?
	//
}


void Engine::Uninit()
{


	//SDL Uninit
	atexit(SDL_Quit);
	
}

