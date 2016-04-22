#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include "Core.h"
#include "ResourceBase.h"


class ImageResource
	: public ResourceBase
{
public:
	ImageResource(SDL_Surface* image) : ResourceBase(resourcefilepath, nullptr)
	{
		_image = image;
		setWidth(image->w);
		setHeight(image->h);
		setPixelData(image->pixels);
		//_image = image;
		//_width = 0;
		//_height = 0;
		//_pixelData = 0;
	}
	~ImageResource(){};

	// TODO: FIX GETTERS
	void setWidth(int width){ _width = width; }
	void setHeight(int height){ _height = height; }
	void setPixelData(void* data){ _pixelData = data; }

<<<<<<< HEAD
	int getWidth(){	return _width; }
=======
	int getWidth(){ return _width; }
>>>>>>> refs/remotes/origin/master
	int getHeight(){ return _height; }
	void* getPixelData(){ return &_pixelData; }

private:

	ImageResource &operator=(ImageResource &image)
	{
		if (this == &image)
			return *this;
	}
	SDL_Surface *_image;
	int _width = 0;
	int _height = 0;
	void* _pixelData;
};

#endif