#pragma once
#include "../Library/GameObject.h"

struct IVector2 {
	int x;
	int y;
	IVector2() :IVector2(0, 0) {};
	IVector2(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

class Vector2 {
public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}

	inline Vector2 operator + (const Vector2& v) {
		Vector2 out;
		out.x = x + v.x;
		out.y = y + v.y;
		return out;
	}

	inline Vector2 operator += (const Vector2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	inline Vector2 operator - (const Vector2& v) {
		Vector2 out;
		out.x = x - v.x;
		out.y = y - v.y;
		return out;
	}

	inline Vector2 operator -= (const Vector2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	inline Vector2 operator * (float scale) {
		Vector2 out;
		out.x = x * scale;
		out.y = y * scale;
		return out;
	}

	inline Vector2 operator *= (float scale) {
		Vector2 out;
		x *= scale;
		y *= scale;
		return *this;
	}

	inline Vector2 operator / (float scale) {
		Vector2 out;
		out.x = x / scale;
		out.y = y / scale;
		return out;
	}

	inline Vector2 operator /= (float scale) {
		Vector2 out;
		x /= scale;
		y /= scale;
		return *this;
	}

	inline float Length() {
		return sqrtf(x * x + y * y);
	}

	inline float LengthSquare() {
		return x * x + y * y;
	}

	inline float Dot(Vector2 v) {
		return x * v.x + y * v.y;
	}

	inline float Cross(Vector2 v) {
		return x*v.y -  y*v.x;
	}
};

inline float Dot(Vector2 v1, Vector2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

inline float Cross(Vector2 v1, Vector2 v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

class Object2D : public GameObject {
public:
	Object2D() : position(Vector2(0, 0)), hImage(-1) {}
	virtual ~Object2D() {}
	virtual void Draw() override;
protected:
	Vector2 position;
	int hImage;
};