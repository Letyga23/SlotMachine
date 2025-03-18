#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <map>
#include "DebugLog.h"

class WorkingWithTextures
{
	static const char* resourceNames[];
	static std::map<int, GLuint> textureCache;

public:
	static int getCountTexture();
	static GLuint loadTexture(const char* filename);
	static GLuint loadTextureFromResource(HINSTANCE hInstance, int index);
	static void drawTexture(GLuint textureID, float x, float y, float width, float height);
	void deleteTexture(GLuint textureID);
	static GLuint getTextureFromCache(HINSTANCE hInstance, int index);
};

