#include "OpenGL.h"

OpenGL::OpenGL()
{
}

OpenGL::~OpenGL()
{
}

// Draw functions
void OpenGL::box(GLfloat x, GLfloat y, GLfloat xLen, GLfloat yLen, GLfloat r, GLfloat g, GLfloat b)
{
	glColor3f(r, g, b);

	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + xLen, y);
	glVertex2f(x, y + yLen);
	glVertex2f(x + xLen, y + yLen);
	glEnd();
}

void OpenGL::boxLine(GLfloat width, GLfloat x, GLfloat y, GLfloat xLen, GLfloat yLen, GLfloat r, GLfloat g, GLfloat b)
{
	GLfloat glTemp[1];
	glGetFloatv(GL_LINE_WIDTH, glTemp);

	glColor3f(r, g, b);
	glLineWidth(width);

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + xLen, y);
	glVertex2f(x, y + yLen);
	glVertex2f(x + xLen, y + yLen);
	glEnd();

	glLineWidth(glTemp[0]);
}

void OpenGL::line(GLfloat width, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b)
{
	GLfloat glTemp[1];
	glGetFloatv(GL_LINE_WIDTH, glTemp);

	glColor3f(r, g, b);
	glLineWidth(width);

	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glLineWidth(glTemp[0]);
}

void OpenGL::dot(GLfloat size, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b)
{
	GLfloat glTemp[1];
	glGetFloatv(GL_POINT_SIZE, glTemp);

	glColor3f(r, g, b);
	glLineWidth(size);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

	glLineWidth(glTemp[0]);
}
