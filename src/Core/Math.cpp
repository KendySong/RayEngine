#include <Limits>

#include "Math.hpp"
#include "../Settings.hpp"

float Math::length(const Vector2& a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

float Math::length(const Vector3& a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

float Math::distance(const Vector2& a, const Vector2& b)
{
	return Math::length(b - a);
}

float Math::distance(const Vector3& a, const Vector3& b)
{
	return Math::length(b - a);
}

Vector2 Math::normalize(const Vector2& a)
{
	return a / Math::length(a);
}

Vector3 Math::normalize(const Vector3& a)
{
	float length = Math::length(a);
	if (length <= 1e-6)
	{
		return { 0, 0, 0 };
	}
	return a / length;
}

Vector2 Math::random(float xMin, float xMax, float yMin, float yMax)
{
	float tx = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float ty = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return { tx * (xMax-xMin) + xMin, ty * (yMax - yMin) + yMin };
}

int Math::random(int min, int max)
{
	return (max - min) * ((float)(rand()) / (float)(RAND_MAX)) + min;
}

float Math::random(float min, float max)
{
	return (max - min) * ((float)rand() / (float)RAND_MAX) + min;
}

Vector2 Math::lerp(const Vector2& a, const Vector2& b, float t)
{
	return (b - a) * t + a;
}

float Math::dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

float Math::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Math::cross(const Vector3& a, const Vector3& b)
{
	return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

bool Math::lineIntersect(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, Vector2* o)
{
	Vector2 ab = b - a;
	Vector2 cd = d - c;
	Vector2 ac = c - a;

	float det = Math::det(ab, cd);
	if (det == 0)
	{
		return false;
	}
	
	float t1 =  (cd.y  * ac.x - cd.x * ac.y) / det;
	float t2 = -(-ab.y * ac.x + ab.x * ac.y) / det;
	
	
	if (Math::distance(a + ab * t1, c + cd * t2) < 0.001f && (t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0))
	{
		*o = a + ab * t1;
		return true;
	}
	
	return false;
}

Vector3 Math::lerp(const Vector3& a, const Vector3& b, float t)
{
	return (b - a) * t + a;
}

float Math::alerp(float a, float b, float x)
{
	return (x - a) / (b - a);
}

Vector2 Math::project(const Vector2& a, const Vector2& b)
{
	return a * (float)(Math::dot(a, b) / Math::dot(a, a));
}

Vector3 Math::project(const Vector3& a, const Vector3& b)
{
	return a * (float)(Math::dot(a, b) / Math::dot(a, a));
}

Vector2 Math::normal(const Vector2& a)
{
	return { -a.y, a.x };
}

Vector2 Math::reflect(const Vector2& a, const Vector2& n)
{
	Vector2 t = Math::normal(n);

	float lambdaN  = Math::dot(a, n);
	float lambdaT = Math::dot(a, t);

	return n * -lambdaN + t * lambdaT;
}

Vector3 Math::reflect(const Vector3& a, const Vector3& n)
{
	Vector3 normal = Math::normalize(n);
	return a - normal * 2 * Math::dot(a, normal);
}

float Math::det(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

float Math::crossDirection(const Vector2& a, const Vector2& b)
{
	//Cross product is outside so det is positive so rotation direction is counter clock wise
	return Math::det(a, b) > 0 ? 1 : -1;
}

float Math::sgn(const float& a)
{
	if (a > 0)
	{
		return 1;
	}
	
	if (a < 0)
	{
		return -1;
	}

	return 0;
}

float Math::angle(const Vector2& a)
{
	return atan2(a.y, a.x);
}

float Math::angle(const Vector2& a, const Vector2& b)
{
	return angle(b) - angle(a);
}

Vector2 Math::rotate(const Vector2& a, float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	return { c*a.x - s*a.y, s*a.x + c*a.y };
}

float Math::clamp(float min, float max, float a)
{
	if (a < min)
	{
		return min;
	}

	if (a > max)
	{
		return max;
	}

	return a;
}

Vector2 operator*(float a, const Vector2& v)
{
	return { a * v.x, a * v.y };
}

Vector3 operator*(float a, const Vector3& v)
{
	return { a * v.x, a * v.y, a * v.z };
}

Vector3 operator-(const Vector3& v)
{
	return { -v.x, -v.y, -v.z };
}

b3Quat operator*(const b3Quat& a, const b3Quat& b)
{
	return b3MulQuat(a, b);
}