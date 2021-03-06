#ifndef CORE_H
#define CORE_H
void extern gameLoop();
void extern gameInit();
void extern userUnInit();
#include <stdio.h>

//Glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
//SDL

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
//RapidXML
#include "RapidXML/rapidxml.hpp"

//FreeType
#include <freetype-2.6.1/include/ft2build.h>
//#include FT_FREETYPE_H
#include "SceneManager.h"
#include "SpriteManager.h"
#include "ResourceManager.h"
#include "ResourceMap.h"
#include "ResourceBase.h"
#include "Resources.h"
#include "Input.h"
#include "SoundFX.h"
#include "Music.h"
#include "ShaderManager.h"
#include "Object3D.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "Sprite.h"
#include "GraphicContext.h"
#include "BufferManager.h"
#include "GameObjectManager.h"

//Assimp
#include <assimp/Importer.hpp>
class TextureManager;
class BufferManager;
class Texture;
class GameObject;
class GameObjectManager;

namespace graphics
{
	class ShaderManager;
	class Sprite;
	class SpriteManager;
}
namespace core
{

	//class SpriteManager;
	class Engine
	{
	public:
		static Engine* UI();
		void Init();
		void Uninit();
		bool run();
		void userInit();
		void quit(){ _exit = true; }
		void createScreen(int ResX, int ResY);
		graphics::Sprite * createSprite(Texture * texture, glm::vec2 position, glm::vec2 size, int z, Color col);
		Texture * createTexture(std::string filepath);
		// Create a sound effect object from a WAV, MP3, OGG or MOD file
		SoundFX * createSoundEffect(std::string filepath);
		// Create a music object from a WAV, MP3, OGG, FLAC or MOD file
		Music * createMusic(std::string filepath);
		Scene * createScene()
		{
			return nullptr;
			//return _scnMngr->createScene(); 
		}
		GameObject* createGameObject();

		//TODO: Needs to read managers from scene and set them as current
		bool useScene(Scene * sc){ return true; }
		core::Input * getInput(){ return _input; }
		Resources * getResources(){ return _resMngr; }
		TextureManager * getTextureManager(){ return _txtrMngr; }
		graphics::SpriteManager * getSpriteManager(){ return _sprtMngr; }
		GraphicContext* getGraphicContext(){ return _grapCtx; }
		graphics::ShaderManager* getShaderManager(){ return _shdrMngr; }
		BufferManager * getBufferManager(){ return _bufMngr; }
		GameObjectManager* getGameObjectManager(){ return _goMngr; }



		//updateGameObjects(float deltaTime);
		//void drawSprites(){ _sprtMngr->drawSprites(); }


		//TestBench to try out modules
		void testInit(Camera* cam, GLfloat screenWidth, GLfloat screenHeight);
		void testUpdate(Camera* cam, float deltaTime, const glm::vec2 mousePosition, const char* input);
		////
	protected:
		virtual ~Engine();
		Engine();

		//TO DO:
		//shaderManager = nullptr;
		//audioManager = nullptr;
		//3DobjectManager = nullptr;
		TextureManager * _txtrMngr;
		AudioManager * _sndMngr;
		BufferManager * _bufMngr;
		core::SceneManager *_scnMngr;
		graphics::SpriteManager * _sprtMngr;
		graphics::ShaderManager* _shdrMngr;
		Resources * _resMngr;
		GraphicContext* _grapCtx;
		GameObjectManager* _goMngr;
			
	private:
		core::Input * _input;
		bool _mainInit; //Has main initialization been done
		bool _audioInit; // Has audio initialization been done
		bool _exit; //Has exit been called
		static Engine *_instance;
		//Handles SDL input events
		void processInput();
	};
}

#endif