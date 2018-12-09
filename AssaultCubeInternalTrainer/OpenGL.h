#pragma once

#include <Windows.h>
#pragma comment(lib, "OpenGL32.lib")
#include <gl\GL.h>


#include "HelpFunctions.h"
class OpenGL
{
public:
	
	
	OpenGL();
	~OpenGL();
	 
	// Draw functions
	void box(GLfloat x, GLfloat y, GLfloat xLen, GLfloat yLen, GLfloat r, GLfloat g, GLfloat b);
	void boxLine(GLfloat width, GLfloat x, GLfloat y, GLfloat xLen, GLfloat yLen, GLfloat r, GLfloat g, GLfloat b);
	void line(GLfloat width, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b);
	void dot(GLfloat size, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
};

