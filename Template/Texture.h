#ifndef TEXTURE_H
#define TEXTURE_H

<<<<<<< HEAD
#include "Core.h"
=======
>>>>>>> refs/remotes/origin/master
#include <string.h>
#include "TextureManager.h"
//#include "ImageResource.h"
class ImageResource;

class Texture
{
public:
	friend class TextureManager;
<<<<<<< HEAD
=======
	Texture(){};
>>>>>>> refs/remotes/origin/master
	Texture(TextureManager* texM)
	{
		_texM = texM;
		_texture = NULL;
	}
	~Texture(){};
	GLuint createTexture(const std::string& resourcefilepath);
	//GLuint bindTexture(ImageResource *img);
	void unbindTexture();


private:

	Texture &operator=(Texture &texture)
	{
		if (this == &texture)
			return *this;
	}

	//TODO: oma mappi textuureille, joku systeemi hakemaan handle samaa filua ladattaessa?
	std::unordered_map<std::string, GLuint>textureMap;
	GLuint _texture;
	ImageResource *_image;
	Resources *_res;
	TextureManager* _texM;

};

#endif