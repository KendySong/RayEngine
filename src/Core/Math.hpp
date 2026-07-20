#pragma once
#define _USE_MATH_DEFINES
#define ALMOST_PI_2_MIN PI / 2 + 0.01f
#define ALMOST_PI_2_MAX PI / 2 - 0.01f

#include <iostream>
#include <vector>
#include <math.h>
#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <box3d/box3d.h>

class Math
{
public :
	static float length(const Vector2& a);
	static float length(const Vector3& a);
	static float distance(const Vector2& a, const Vector2& b);
	static float distance(const Vector3& a, const Vector3& b);
	static Vector2 normalize(const Vector2& a);
	static Vector3 normalize(const Vector3& a);
	static Vector2 random(float xMin, float xMax, float yMin, float yMax);
	static int random(int min, int max);
	static float random(float min, float max);
	static Vector2 lerp(const Vector2& a, const Vector2& b, float t);
	static float dot(const Vector2& a, const Vector2& b);
	static float dot(const Vector3& a, const Vector3& b);
	static Vector3 cross(const Vector3& a, const Vector3& b);
	static bool lineIntersect(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, Vector2* o);
	static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
	static float alerp(float a, float b, float x);
	static Vector2 project(const Vector2& a, const Vector2& b);
	static Vector3 project(const Vector3& a, const Vector3& b);
	static Vector2 normal(const Vector2& a);

	static Vector2 reflect(const Vector2& a, const Vector2& n);
	static Vector3 reflect(const Vector3& a, const Vector3& n);
	static float det(const Vector2& a, const Vector2& b);
	
	static float crossDirection(const Vector2& a, const Vector2& b);
	static float sgn(const float& a);
	static float angle(const Vector2& a);
	static float angle(const Vector2& a, const Vector2& b);
	static Vector2 rotate(const Vector2& a, float angle);

	static float clamp(float min, float max, float a);
};

Vector2 operator*(float a, const Vector2& v);
Vector3 operator*(float a, const Vector3& v);
Vector3 operator-(const Vector3& v);
b3Quat  operator*(const b3Quat& a, const b3Quat& b);