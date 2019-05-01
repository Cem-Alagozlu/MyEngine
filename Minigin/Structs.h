#pragma once
struct Vector2f
{
	float x{};
	float y{};
};

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