#pragma once


struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float flen = Length();
		assert(flen != 0.f);
		// 0 이면 나누지 않겠다가 아닌 0이라면 문제라고 판단하여 중단.
		x /= flen;
		y /= flen;
		return *this;
	}

public:

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOhter)
	{
		x += _vOhter.x;
		y += _vOhter.y;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vec2(x / _f, y / _f);
	}
	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator*(float _f)
	{
		return Vec2(x * _f, y * (float)_f);
	}
public:
	Vec2()
		:x(0.f)
		,y(0.f)
	{}

	Vec2(float _x,float _y)
		:x(_x)
		,y(_y)
	{}

	Vec2(int _x,int _y)
		:x((float)_x)
		,y((float)_y)
	{}
	Vec2(const POINT& _pt)
		:x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};
// 힘 , 크기를 갖고 있는 벡터