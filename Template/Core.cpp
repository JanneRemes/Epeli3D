#include "Core.h"

using namespace core;
Engine* core::Engine::_instance = nullptr;
Engine::Engine() :_mainInit(false), _exit(false)
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
Engine* Engine::UI()
{
	if (_instance == nullptr)
	{
		_instance = new Engine();
	}
	return _instance;
}
bool Engine::run()
{
	userInit();
	while(true)
	{
		gameLoop();
		if (_exit)
			return _exit;
	}
}
void Engine::userInit()
{ 
	if (_mainInit)
		return; 
	gameInit(); 
};
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

	// SDL audio init
	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG) != flags)
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_audio: %s\n", SDL_GetError());
	}
	flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP;
	// SDL image init
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) != flags)
	{
		fprintf_s(stderr, "\nUnable to initialize SDL_image: %s\n", SDL_GetError());
	}
	
	//GlewInit()
	glewExperimental = GL_TRUE;

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

