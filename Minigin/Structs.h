#pragma once
struct Vector2f
{
	float x{};
	float y{};
};

inline Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs)
{
	float x = lhs.x + rhs.x;
	float y = lhs.y + rhs.y;

	Vector2f newVec{ x,y };

	return newVec;
}

struct Color3i
{
	int r{};
	int g{};
	int b{};
};

struct Rectf
{
	Rectf();
	Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;
};

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
inline Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

inline Rectf::Rectf(float left, float bottom, float width, float height)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
{
}