#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include <vector>

#define _INIT_SIZE 50.0f

class Shape :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Shape();
	~Shape() { };

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	
private:
	void DrawOctahedron();
	void Subdivision(int n, std::vector<float> l, std::vector<float> r, std::vector<float> t);
	float GetMagnitude(std::vector<float> v);
	int x;
	std::vector< std::vector<float> > list;

	// key press flags
	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset;
};