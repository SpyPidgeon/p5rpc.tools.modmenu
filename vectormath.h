#pragma once

struct Vector3
{
	Vector3() : x(0),y(0),z(0) {}
	Vector3(float x,  float y, float z) : x(x),y(y),z(z) {}
	~Vector3() {}
	float x, y, z;
};