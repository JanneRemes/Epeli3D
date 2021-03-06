#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Color.h"
/*
	Basic functions for a drawable objects
	Rotations are in degrees in glm::vec3 rotations
*/
namespace graphics
{
	class Drawable
	{
	public:
		//Changes current color
		void changeColor(Color newColor){ color = newColor; }
		//Sets position to
		void moveTo(glm::vec3 to){ _position = to; }
		//Adds vector "by" to current position
		glm::vec3 moveBy(glm::vec3 by){ return _position + by; }
		//Rotates all axis by given values glm::vec3(x,y,z)
		void rotate(glm::vec3 rotateBy){ _rotations += rotateBy; }
		void rotateX(float degrees){ _rotations.x += degrees; }
		void rotateY(float degrees){ _rotations.y += degrees; }
		void rotateZ(float degrees){ _rotations.z += degrees; }

		//Sets rotation of all axis to given values glm::vec3(x,y,z)
		void rotateTo(glm::vec3 rotations){ _rotations = rotations; }
		
		void scale(float _scaleBy){ _scale = _scaleBy; }
		//Returns current position
		glm::vec3 getPosition(){ return _position - _origin; }
		//glm::mat4 &getModelMatrix(){ return matrix; }
		Color color;
	protected:
		//Checks if rotation or scaling has changed
		//Needs to recalculate drawing bounds
		bool checkUpdate()
		{ 
			if (_oldRotations == _rotations && _oldScale == _scale)
				return _needUpdate = false; 
			_oldRotations = _rotations;
			_oldScale = _scale;
			return _needUpdate = true;
		}
		//Apply to base values
		glm::mat4 getTransfMat()
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(_scale, _scale, _scale));

			glm::mat4 rot = glm::rotate(glm::mat4(1.0), _rotations.x, glm::vec3(1, 0, 0));
			rot = glm::rotate(rot, _rotations.y, glm::vec3(0, 1, 0));
			rot = glm::rotate(rot, _rotations.z, glm::vec3(0, 0, 1));
		
			glm::mat4 translate = glm::translate(glm::mat4(1.0), _position);

			matrix = translate * rot * scale;
			return matrix;		
		}
		Drawable(glm::vec3 position) :_position(position), _rotations(0, 0, 0), _scale(1.0), _origin(0, 0, 0){};
		Drawable(glm::vec3 position,glm::vec3 origin) :_position(position), _rotations(0, 0, 0), _scale(1.0), _origin(origin){};
		Drawable() :_position(0, 0, 0), _rotations(0, 0, 0), _scale(1.0),_origin(0, 0, 0){};
		Drawable(glm::vec3 position, glm::vec3 origin, Color col) :_position(position), _rotations(0, 0, 0), _scale(1.0), _origin(origin),color(col){};
		~Drawable(){};		
	private:
		glm::mat4 matrix;
		glm::vec3 _origin;
		glm::vec3 _position;
		glm::vec3 _rotations;
		float _scale;

		glm::vec3 _oldRotations;
		float _oldScale;
		bool _needUpdate;
	};
}
#endif