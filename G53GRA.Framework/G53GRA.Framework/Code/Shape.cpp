#include "Shape.h"
#include <iostream>

Shape::Shape() :
_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	size(_INIT_SIZE);

	// number of subdivision iterations
	x = 4; // CHANGE ME FOR DIFFERENT RESULTS! *Be warned, 6+ has impact on performance, recommended 1-5 range. 
	
	std::vector< std::vector<float> > list; // list of vertices from the subdivision result

	float r = 1.f; // radius
	std::vector<float> f(3), l(3), rs(3), t(3), b(3), ba(3); // Each vertex of the original octahedron
	f = { 0, 0, r }; // front vertex
	l = { -r, 0, 0 }; // left vertex
	rs = { r, 0, 0 }; // right vertex
	t = { 0, r, 0 }; // top vertex
	b = { 0, -r, 0 }; // bottom vertex
	ba = { 0, 0, -r }; // back vertex

	// only call subdivide if needed
	if (x != 0) {
		// subdivision for each of the 8 octahedron faces
		Subdivision(x, f, rs, t);
		Subdivision(x, f, b, rs);
		Subdivision(x, rs, ba, t);
		Subdivision(x, rs, b, ba);
		Subdivision(x, ba, l, t);
		Subdivision(x, ba, b, l);
		Subdivision(x, l, f, t);
		Subdivision(x, l, b, f);
	}
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

	// seed random number generator for consistent red colours
	srand(100);

	// draw the subdivided octahedron (sphere)
	DrawOctahedron();

	// Reenable default lighting (IGNORE THIS)
	glEnable(GL_LIGHTING);
	// Revert changes between most recent glPushMatrix and here
	glPopMatrix();
}

void Shape::DrawOctahedron()
{
	//construct from triangles
	glBegin(GL_TRIANGLES);

	// if no subdivision occurs, draw octahedron normally with random shades of red
	if (x == 0) {
		float r = 1.f;
		// Top Half
		// Front-Right Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(0, 0, r);
		glVertex3f(r, 0, 0);
		glVertex3f(0, r, 0);
		// Back-Right Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(r, 0, 0);
		glVertex3f(0, 0, -r);
		glVertex3f(0, r, 0);
		// Back-Left Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(0, 0, -r);
		glVertex3f(-r, 0, 0);
		glVertex3f(0, r, 0);
		// Front-Left Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(-r, 0, 0);
		glVertex3f(0, 0, r);
		glVertex3f(0, r, 0);
		// Bottom Half
		// Front-Right Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(r, 0, 0);
		glVertex3f(0, 0, r);
		glVertex3f(0, -r, 0);
		// Back-Right Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(0, 0, -r);
		glVertex3f(r, 0, 0);
		glVertex3f(0, -r, 0);
		// Back-Left Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(-r, 0, 0);
		glVertex3f(0, 0, -r);
		glVertex3f(0, -r, 0);
		// Front-Left Face
		glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);
		glVertex3f(0, 0, r);
		glVertex3f(-r, 0, 0);
		glVertex3f(0, -r, 0);
	} else { // get x, y and z from 3 entries in the subdivision resultant list of vertices and construct a triangle from them
		for (unsigned i = 0; i < list.size() - 2; i += 3) {

			// set colour to a random shade of red to demonstrate triangular construction of sphere
			glColor3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0.f, 0.f);

			glVertex3f(list[i][0], list[i][1], list[i][2]);
			glVertex3f(list[i + 1][0], list[i + 1][1], list[i + 1][2]);
			glVertex3f(list[i + 2][0], list[i + 2][1], list[i + 2][2]);

		}
	}
	glEnd();
}

void Shape::Subdivision(int n, std::vector<float> l, std::vector<float> r, std::vector<float> t)
{

	// Midpoint Vectors
	std::vector<float> v1(3), v2(3), v3(3);
	v1 = { (float) ((l[0] + t[0]) / 2), (float) ((l[1] + t[1]) / 2), (float) ((l[2] + t[2]) / 2) };
	v2 = { (float) ((l[0] + r[0]) / 2), (float) ((l[1] + r[1]) / 2), (float) ((l[2] + r[2]) / 2) };
	v3 = { (float) ((t[0] + r[0]) / 2), (float) ((t[1] + r[1]) / 2), (float) ((t[2] + r[2]) / 2) };

	// Calculate where the vertex should be pushed/moved to via normalization
	v1 = { (float) (v1[0] / GetMagnitude(v1)), (float) (v1[1] / GetMagnitude(v1)), (float) (v1[2] / GetMagnitude(v1)) };
	v2 = { (float) (v2[0] / GetMagnitude(v2)), (float) (v2[1] / GetMagnitude(v2)), (float) (v2[2] / GetMagnitude(v2)) };
	v3 = { (float) (v3[0] / GetMagnitude(v3)), (float) (v3[1] / GetMagnitude(v3)), (float) (v3[2] / GetMagnitude(v3)) };

	// add resultants vertices from each subdivision into the list
	if ( n == 1 ) {
		list.push_back(l);
		list.push_back(v2);
		list.push_back(v1);

		list.push_back(v1);
		list.push_back(v2);
		list.push_back(v3);

		list.push_back(v2);
		list.push_back(r);
		list.push_back(v3);

		list.push_back(v1);
		list.push_back(v3);
		list.push_back(t);
	}

	// recursively call subdivision on the new triangles from the subdivision
	if ( n != 0 ) {
		Subdivision(n - 1, v1, v3, t);
		Subdivision(n - 1, l, v2, v1);
		Subdivision(n - 1, v2, r, v3);
		Subdivision(n - 1, v1, v2, v3);
	}

	
} 

float Shape::GetMagnitude(std::vector<float> v)
{
	// Pythagoras

	for (int i = 0; i < 3; i++) {
		v[i] = v[i] * v[i];
	}

	return sqrt(v[0] + v[1] + v[2]);
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