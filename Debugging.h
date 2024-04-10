#pragma once
#include <iostream>
#include <ostream>

#include "glad/glad.h"
//opengl error checking code from https://learnopengl.com/In-Practice/Debugging (modified)
inline GLenum glCheckError_(WorldObject* InWorldObject, const char *file, int line, const char* function)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}

		//check if the world object is valid
		if (InWorldObject != nullptr)
		{
			std::cout << InWorldObject->Name << " | " << error << " | " << file << " (" << line << ") | " << function << std::endl;
		}
		else
		{
			std::cout << error << " | " << file << " (" << line << ") | " << function << std::endl;
		}

		std::cout << error << " | " << file << " (" << line << ") | " << function << std::endl;
	}
	return errorCode;
}
//define for the error checking outside of world objects
#define glCheckError() glCheckError_(nullptr, __FILE__, __LINE__, __FUNCTION__)

//define for the error checking inside of world objects
#define glWCheckError() glCheckError_(this, __FILE__, __LINE__, __FUNCTION__)