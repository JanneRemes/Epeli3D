#ifndef RESOURCEMAP_H
#define RESOURCEMAP_H
#include "Core.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

template <class T>
class ResourceMap
{
public:
	ResourceMap()
	{
		duplicates = -1;			// undetermined state
		ResourceManager = NULL;		// no resource manager assigned
	}

	~ResourceMap()
	{
		clearElements();		// remove elements if unique
	}

	//////////////////////////////////////
	// adds a new element

	T* addElement(const std::string &resourcename, const std::string &filename, void *args = 0)
	{
		if (ResourceManager == NULL)printf_s("Error: DataBase cannot be NULL (5)");
		if (filename.empty())printf_s("%s : filename cannot be null", Name.c_str());
		if (resourcename.empty())printf_s("%s : resourcename cannot be null", Name.c_str());

		// look in the hashmap to see if the resource is already loaded

		std::unordered_map<std::string, T* >::iterator it = Map.find(resourcename);

		if (it == Map.end())
		{
			// if duplicates flag is set to truem duplicated mapped values are allowed
			// if duplicates flag is set to false, duplicates won't be allowed

			if (isValNonUnique(filename))
			{
				T* resource = ResourceManager->Load(filename, args);
				// allocate new resource using the raii paradigm
				Map.insert(std::pair<std::string, T*>(resourcename, resource));

				return resource;
			}
			else
			{
				// if we get here and duplicates flag is set to false
				// the filename is duplicated

				printf_s("Error: filename %s must be unique\n", filename.c_str());
			}
			// if we get here means that resource name is duplicated

			printf_s("Error: Resource name %s must be unique\n", resourcename.c_str());

			return nullptr;
		}
	}

	////////////////////////////////////////
	// delete element using resourceName

	bool removeElement(const std::string &resourcename)
	{
		if (ResourceManager == NULL)printf_s("Error: DataBase cannot be NULL (4)");
		if (resourcename.empty())printf_s("Error: %s: resourceName cannot be NULL", Name.c_str());

		// search for item

		std::unordered_map<std::string, T* >::iterator it = Map.find(resourcename);

		// delete element, reference count will be decreased

		if (it != Map.end())
		{
			// save resource name

			std::string filename = (*it).second->getResourceFileName();

			// erase from this map

			Map.erase(it);

			// check if it is unique and erase it eventually

			ResourceManager->Unload(filename);

			return true;
		}
		// if we get here, node couldn't be found, exit with an error

		printf_s("%s : couldn't delete %s\n", Name.c_str(), resourcename.c_str());
		return false;
	}

	///////////////////////////////////////////////////////
	// clear all the elements from map

	void clearElements()
	{
		std::unordered_map<std::string, T* >::iterator it = Map.begin();
		// walk through the map

		while (it != Map.end())
		{
			// save resource name

			std::string filename = (*it).second->getResourceFileName();

			// erase from this map

			it = Map.erase(it);

			// check if it is unique and erase it eventually

			ResourceManager->Unload(filename);
		}
	}

	//////////////////////////////////////////
	// dumps database content to a string

	void ResourceMap::dump()
	{
		if (ResourceManager == NULL)
			printf("Error: DataBase cannot be NULL (3)");

		printf_s("Dumping database: %s\n\n", ResourceManager->GetName().c_str());
				
		for (std::unordered_map<std::string, T*>::iterator it = Map.begin(); it != Map.end(); it++)
		{
			printf_s("Resourcename: %s, %s\n",
				(*it).first.c_str(),
				(*it).second->getResourceFileName().c_str());
		}
		printf_s("\n\n");
	}
	/////////////////////////////////////////
	// get array name

	const std::string &GetName() const{ return Name; }
	const int size() const { return Map.size(); }

	/////////////////////////////////////////
	// get const reference to resource manager

	const ResourceManager<T> *getResourceManager(){ return ResourceManager; }

	/////////////////////////////////////////
	// get element using resourceName

	T *getElement(const std::string &resourcename)
	{
		if (ResourceManager == NULL)printf_s("DataBase cannot be NULL (2)");
		if (resourcename.empty())printf_s("%s : resourceName cannot be null", Name.c_str());

		std::unordered_map<std::string, T*>::iterator it;

		// searcf for item
		printf_s("Looking for %s", resourcename.c_str());
		it = Map.find(resourcename);
		//return pointer to element
		if (!= Map.end())
			return it->second;

		// if we get here, node couldn't be found
		printf_s("Error: %s : couldn't find %s", Name.c_str(), resourcename.c_str());

		// this point is never reached in case of failure

		return nullptr;
	}
	/////////////////////////////////////
	// setters

	void allowDuplicates(){ duplicates = true; }
	void disallowDuplicates(){ duplicates = false; }

	////////////////////////////////////
	// initialize resource mapper

	void initMapper(const std::string &name, ResourceManager<T> *resourcemanager,
		bool duplicates)
	{
		if (resourcemanager == NULL) printf_s("DataBase cannot be NULL (1)");
		if (name.empty())printf_s("Array name cannot be null");

		ResourceManager = resourcemanager;

		if (duplicates)
			printf_s("%s: Duplicates allowed\n", name.c_str());

		else if (!duplicates)
			printf_s("%s: Duplicates disallowed\n", name.c_str());
	}

private:
	//////////////////////////////
	// find the requested value from the map

	bool isValNonUnique(const std::string &filename)
	{
		// if duplicates are allowed , then return always true

		if (duplicates) 
			return true;

		// else , check if element by value is already present
		// if it is found, then rturn treu, else exit with false

		std::unordered_map<std::string, T*>::iterator it = Map.begin();

		while (it != Map.end())
		{
			if ((it->second->getResourceFileName() == filename)) 
				return false;
			++it;
		}
		return true;
	}

	///////////////////////////////////////////
	// private data

	std::string Name;
	int duplicates;
	ResourceManager<T>*ResourceManager;			// attached resource manager
	std::unordered_map<std::string, T* >Map;	//resource mapper

	ResourceMap(const ResourceMap&){};
	ResourceMap &operator = (const ResourceMap&){ return *this; }
};

#endif