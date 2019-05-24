#pragma once
namespace cem
{
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

	inline Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs)
	{
		float x = lhs.x - rhs.x;
		float y = lhs.y - rhs.y;

		Vector2f newVec{ x,y };

		return newVec;
	}

	inline Vector2f operator*(const Vector2f& lhs, const float& scalar)
	{
		float x = lhs.x * scalar;
		float y = lhs.y * scalar;

		Vector2f newVec{ x,y };

		return newVec;
	}


	inline bool operator==(const Vector2f& lhs, const Vector2f& rhs)
	{
		if (lhs.x == rhs.x && lhs.y == rhs.y)
		{
			return true;
		}
		return false;
	}
	//"heavy function -> inline" 
	inline float Distance(const Vector2f& lhs, const Vector2f& rhs)
	{
		return sqrt(pow((lhs.x - rhs.x), 2) + pow((lhs.y - rhs.y), 2));
	}

	inline Vector2f Normalize(const Vector2f& lhs)
	{
		Vector2f newVector = lhs;
		float magnitude = sqrt(pow(lhs.x, 2) + pow(lhs.y, 2));


		newVector.x /= magnitude;
		newVector.y /= magnitude;

		return newVector;
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
}