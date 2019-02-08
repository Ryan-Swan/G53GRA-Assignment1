#pragma once

#ifdef __APPLE__ // if OS X
#include <glut/glut.h> // include freeglut libraries

#elif __linux__
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#else // if Windows
#include <gl/glut.h> // include freeglut libraries

#endif

#include <stdio.h>

void setup();
void draw();
int main(int argc, char **argv);
void checkGLError();
void reshape(int _width, int _height);

int height, width;
