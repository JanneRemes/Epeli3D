#include "GameObjectManager.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>


GameObjectManager::GameObjectManager(BufferManager *buff)
{
	buffMngr = buff;
	data = new std::vector<Mesh>();
}

GameObjectManager::~GameObjectManager()
{
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end(); gameobject++)
	{
		//delete *gameobject;
		//gameobject = gameObjects.erase(gameobject);
		delete (*gameobject);
	}

	//delete data;
}

void GameObjectManager::update(float deltaTime)
{
	//delete destroyed objects
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end();)
	{
		if ((*gameobject)->isDestroyed())
		{
			delete *gameobject;
			gameobject = gameObjects.erase(gameobject);
			//destroyedGameObjects.push_back((*gameobject));
		}
		else
		{
			gameobject++;
		}		
	}

	//update gameobjects
	for (std::vector<GameObject*>::iterator gameobject = gameObjects.begin(); gameobject != gameObjects.end();)
	{
		(*gameobject)->update(deltaTime);
	}
}

void GameObjectManager::sendDataToBuffer(Shader* shader)
{
	for (auto gameobject = gameObjects.begin(); gameobject != gameObjects.end(); gameobject++)
	{
		if ((*gameobject)->getComponent<ModelComponent>())
		{				
			data = (*gameobject)->getModelData();

			std::vector<Mesh>::iterator modelIter;
			std::vector<Vertex>::iterator vertexIter;
			std::vector<GLuint>::iterator indicesIter;

			std::vector<Vertex> vertexData;
			std::vector<GLuint> indicesData;			

			if ((*gameobject)->getComponent<TransformComponent>())
			{
				//TransformComponent* tempTransform = new TransformComponent((*gameobject)->getComponent<TransformComponent>());
				//modelMat = (*gameobject)->getComponent<TransformComponent>()->getModelMatrix;

				for (modelIter = data->begin(); modelIter != data->end(); modelIter++)
				{
					for (vertexIter = modelIter->vertices.begin(); vertexIter != modelIter->vertices.end(); vertexIter++)
					{	
						//glm::fmat4 tempMat = (*gameobject)->getComponent<TransformComponent>()->getModelMatrix();
						//glm::vec4 tempVec = glm::vec4((*vertexIter).Position, 1.0f);
						//glm::vec4 transform = tempMat * tempVec;

						glm::vec4 transform = (*gameobject)->getComponent<TransformComponent>()->getModelMatrix() * glm::vec4((*vertexIter).Position, 1.0f);

						(*vertexIter).Position = glm::vec3(transform.x, transform.y, transform.z);
						//glUniformMatrix4fv();
						//(*vertexIter).Position = (*gameobject)->getComponent<TransformComponent>()->getModelMatrix() * (*vertexIter).Position;
							vertexData.push_back((*vertexIter));
					}

					for (indicesIter = modelIter->indices.begin(); indicesIter != modelIter->indices.end(); indicesIter++)
					{
						indicesData.push_back((*indicesIter));
					}
				}


				//delete tempTransform;
			} //((*gameobject)->getComponent<TransformComponent>())
						
			buffMngr->addBufferData(vertexData, indicesData);
			//std::vector<Mesh> clear;
			//data->swap(clear);
			//data->clear();
			//delete data;
		} //((*gameobject)->getComponent<ModelComponent>())		
	}//(auto gameobject = gameObjects.begin(); gameobject != gameObjects.end();)	
}

GameObject* GameObjectManager::createGameObject()
{
	GameObject* obj = new GameObject();
	gameObjects.push_back(obj);
	return obj;
}

//GameObject* GameObjectManager::getGameObject();
//{
//
//}

std::vector<GameObject*> GameObjectManager::getGameObjects()
{
	return gameObjects;
}