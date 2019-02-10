#include "Shape.h"
#include <iostream>

Shape::Shape() :
_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	size(_INIT_SIZE);
}

void Shape::Display()
{ 
	// Push the current transformation matrix.
	// for now just put it at the start and end of each draw call you make
	glPushMatrix();

	// Disable default lighting effects (IGNORE THIS)
	glDisable(GL_LIGHTING);

	// Translate object into its position first
	glTranslatef(pos[0], pos[1], pos[2]);

	// Scale object (but not translation) by calling scale after translate
	glScalef(scale[0], scale[1], scale[2]);

	// Rotate object in new position, in order y>z>x axes
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	// Local function to draw coloured cube
	DrawCube(true); // standalone cube

	// Translate object to the left of the cube
	glTranslatef(pos[0] - 3.f, pos[1], pos[2]);
	DrawTetrahedron(); // draw standalone tetrahedron

	// Translate objects to the right of the cube
	glTranslatef(pos[0] + 6.f, pos[1], pos[2]);
	DrawCube(false); // draw wireframe cube
	DrawTetrahedron(); // draw tetrahedron inside cube

	// Reenable default lighting (IGNORE THIS)
	glEnable(GL_LIGHTING);
	// Revert changes between most recent glPushMatrix and here
	glPopMatrix();
}

void Shape::DrawCube(bool type)
{
	float r = 1.f;

	// Draw with Triangles (Solid, NOT wireframe) if passed in
	if (type) glBegin(GL_TRIANGLES);

	// Near face
    // Left Triangle
	glColor3f(0.8f, 0.f, 0.f); // Colour to use for when wireframe version doesn't override
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, -r, r);
	glVertex3f(r, r, r);
	glVertex3f(-r, r, r);
	if (!type) glEnd();

	// Right Triangle
	glColor3f(0.9f, 0.f, 0.f); // Switch colour slightly for clarity and to help demonstrate triangular construction has been used, instead of a quads construction
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, -r, r);
	glVertex3f(r, -r, r);
	glVertex3f(r, r, r);
	if (!type) glEnd();


	// Right face
	// Near Triangle
	glColor3f(0.f, 0.8f, 0.f);
	if (!type) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.7f, 0.7f, 0.7f);
	}
	glVertex3f(r, -r, r);
	glVertex3f(r, r, -r);
	glVertex3f(r, r, r);
	if (!type) glEnd();

	// Back Triangle
	glColor3f(0.f, 0.9f, 0.f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(r, -r, r);
	glVertex3f(r, -r, -r);
	glVertex3f(r, r, -r);
	if (!type) glEnd();

	
	// Back face
	// Left (if viewed from face) Triangle (Right if viewed from/through near face)
	glColor3f(0.f, 0.f, 0.8f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(r, -r, -r);
	glVertex3f(-r, -r, -r);
	glVertex3f(r, r, -r);
	if (!type) glEnd();

	
	// Right (if viewed from face) Triangle (Left if viewed from/through near face)
	glColor3f(0.f, 0.f, 0.9f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, -r, -r);
	glVertex3f(-r, r, -r);
	glVertex3f(r, r, -r);
	if (!type) glEnd();

	
	// Left face
	// Back triangle
	glColor3f(0.f, 0.8f, 0.8f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, -r, -r);
	glVertex3f(-r, -r, r);
	glVertex3f(-r, r, -r);
	if (!type) glEnd();

	
	// Near triangle
	glColor3f(0.f, 0.9f, 0.9f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, -r, r);
	glVertex3f(-r, r, r);
	glVertex3f(-r, r, -r);
	if (!type) glEnd();

	
	// Top face
	// Left triangle
	glColor3f(0.8f, 0.8f, 0.f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, r, r);
	glVertex3f(r, r, -r);
	glVertex3f(-r, r, -r);
	if (!type) glEnd();

	// Right triangle
	glColor3f(0.9f, 0.9f, 0.f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, r, r);
	glVertex3f(r, r, r);
	glVertex3f(r, r, -r);
	if (!type) glEnd();

	
	// Bottom face
	// Right triangle (if viewed from bottom face)
	glColor3f(0.8f, 0.f, 0.8f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(r, -r, -r);
	glVertex3f(r, -r, r);
	glVertex3f(-r, -r, r);
	if (!type) glEnd();

	// Left triangle (if viewed from bottom face)
	glColor3f(0.9f, 0.f, 0.9f);
	if (!type) {
		glBegin(GL_LINE_LOOP); // Use line loops if wireframe is desired
		glColor3f(0.7f, 0.7f, 0.7f); // set wireframe colour to grey
	}
	glVertex3f(-r, -r, -r);
	glVertex3f(r, -r, -r);
	glVertex3f(-r, -r, r);
	glEnd();
}

void Shape::DrawTetrahedron()
{
	float r = 1.f;

	glBegin(GL_TRIANGLES); // Triangle Construction, 1 per face, using specific vertices selected from cube
						   // Using same colours to help show the stand-alone object fits inside the cube (via wireframe)

	// Near face
	glColor3f(1.f, 1.f, 0.f);
	glVertex3f(-r, -r, r); 
	glVertex3f(r, -r, -r); 
	glVertex3f(r, r, r); 

	// Left face
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(-r, r, -r); 
	glVertex3f(-r, -r, r); 
	glVertex3f(r, r, r); 

	// Right face
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(r, -r, -r); 
	glVertex3f(-r, r, -r); 
	glVertex3f(r, r, r); 

	// Bottom face
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(r, -r, -r); 
	glVertex3f(-r, -r, r); 
	glVertex3f(-r, r, -r); 

	glEnd();
}

void Shape::Update(const double& deltaTime)
{
	/*
	The update function gives a smooth motion between frames.
	Update is called before drawing every frame so we can use it to
	update the cubes position and rotation each frame.
	The input argument (deltaTime) gives you how many seconds
	have passed between calling the Update function, so we can
	use it define the speed of an object. If we want a object to 
	transform by 100 units each second and deltaTime represents 
	how many seconds have passed betweeen rendering the last frame
	and the this then we can multiply 100*deltaTime to calculate
	the tranform for this frame at a rate of 100 units per second.
	*/
	float velocity = 100.0f*static_cast<float>(deltaTime);
	float shrinkRate = -50.0f*static_cast<float>(deltaTime);

	// Spacebar will reset transformation values
	if (_flagReset)
	{
		orientation(0.0f, 0.0f, 0.0f);
		size(_INIT_SIZE);
		position(0.0f, 0.0f, 0.0f);
		_flagReset = false;
	}

	/*
	If keys pressed down:
	[u][i][o]
	 [j][k][l]
	 
	 rotate around x,y,z axes for (i,k), (j,l) and (u,o) respectively
	*/
	
	// 'i' pressed down, decrease rotation around 'x'
	if (_iKey) rotation[0] -= velocity;
	// 'j' pressed down, decrease rotation around 'y'
	if (_jKey) rotation[1] -= velocity;
	// 'k' pressed down, increase rotation around 'x'
	if (_kKey) rotation[0] += velocity;
	// 'l' pressed down, increase rotation around 'y'
	if (_lKey) rotation[1] += velocity;
	// 'o' pressed down, decrease rotation around 'z'
	if (_oKey) rotation[2] -= velocity;
	// 'u' pressed down, increase rotation around 'x'
	if (_uKey) rotation[2] += velocity;

	/*
	If keys pressed down:
	[-]	
	|+|  or   [-]^[+]
	|_|

	scale by all x,y,z axes equally, + to grow, - to shrink
	*/
	// '-' pressed down (and no scale value is below 1.0)
	if (_minusKey && scale[0] > 1.0f && scale[1] > 1.0f && scale[2] > 1.0f)
	{
		// increase shrinkage by constant (negative) rate
		scale[0] += shrinkRate;
		scale[1] += shrinkRate;
		scale[2] += shrinkRate;
	}
	// '+' pressed down
	if (_plusKey)
	{
		// decrease shrinkage (e.g. grow)
		scale[0] -= shrinkRate;
		scale[1] -= shrinkRate;
		scale[2] -= shrinkRate;
	}

	/*
	If keys pressed down:
	    [/\]
	[<-][\/][->]

	translate along x and y axes, for (left, right) and (up, down) respectively
	*/
	if (_upKey) pos[1] += velocity;
	if (_downKey) pos[1] -= velocity;
	if (_leftKey) pos[0] -= velocity;
	if (_rightKey) pos[0] += velocity;
}

void Shape::HandleKey(unsigned char key, int state, int x, int y)
{
	/*
	This function is called continuously when a key is pressed AND when
	it is released. The variable 'key' describes the character or the key,
	e.g. for the a key, key == 'a'. Variable 'state' describes whether the
	key has been pressed or released. While the key is pressed, state = 1,
	when released, the function is called with state = 0. x and y describe
	position of the mouse at callback (this can be ignored for now).
	*/

	// Switch on key char
	// Set flag for control keys, (i,j,k,l,o,u,+,-,space) to state value
	// i.e. if 'i' is pressed, _iKey = true, if 'i' released, _iKey = false
	switch (key)
	{
	case 'i':
		_iKey = static_cast<GLboolean>(state);
		break;
	case 'j':
		_jKey = static_cast<GLboolean>(state);
		break;
	case 'k':
		_kKey = static_cast<GLboolean>(state);
		break;
	case 'l':
		_lKey = static_cast<GLboolean>(state);
		break;
	case 'o':
		_oKey = static_cast<GLboolean>(state);
		break;
	case 'u':
		_uKey = static_cast<GLboolean>(state);
		break;
	case '+': // with shift
	case '=': // without shift
		_plusKey = static_cast<GLboolean>(state);
		break;
	case '-':
		_minusKey = static_cast<GLboolean>(state);
		break;
	case ' ':
		_flagReset = true;
		break;
	}
}

void Shape::HandleSpecialKey(int key, int state, int x, int y)
{
	/*
	This function is called continuously when a special key is pressed
	AND when it is released. The variable 'key' describes the keycode
	for the key, e.g. for the UP key, key == 0x0065 (or GLUT_KEY_UP).
	Variable 'state' describes whether the key has been pressed or
	released. While the key is pressed, state = 1, when released, the
	function is called with state = 0. x and y describe position of the
	mouse at callback.

	See the Lab 4 for details on special keys. 
	*/

	// Switch on key code (using GLUT #defines)
	// Set flag for control keys, (up, down, left, right) to state value
	// i.e. if 'up' is pressed, _upKey = true, if 'up' released, _upKey = false
	switch (key)
	{
	case GLUT_KEY_UP:
		_upKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_DOWN:
		_downKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_LEFT:
		_leftKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_RIGHT:
		_rightKey = static_cast<GLboolean>(state);
		break;
	}
}