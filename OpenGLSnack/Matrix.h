
//
//  Maxtix.h
//  OpenGLSnack
//
//  Created by ZhaoPeiWei on 16/1/10.
//  Copyright © 2016年 ZhaoPeiWei. All rights reserved.
#pragma once

#include <stdio.h>

class Vector
{
public:
    Vector(int m = 1) : _m(m)
    {
        _data = new float[m];
    }
    Vector(const Vector& r)
	{
		_m = r._m;
		_data = new float[_m];
		for (int i = 0; i < _m; ++i)
		{
			_data[i] = r._data[i];
		}
	}
	~Vector()
	{
		delete []_data;
	}

	float dot(const Vector& o) const
	{
		float r = 0;
		for (int i = 0; i < _m; ++i)
		{
			r += _data[i] * o._data[i];
		}
		return r;
	}

	int _m;
	float* _data;
};

class Matrix
{
public:
	Matrix(int m=1 , int n=1);
	~Matrix();

	void init(float * data)
	{
		int count = _m*_n;
		for (int i = 0; i < count; ++i)
		{
			_data[i] = data[i];
		}
	}

	Matrix operator +(const Matrix& o) const
	{
		Matrix r(_m, _n);
		for (int i = 0; i < _count; ++i)
		{
			r._data[i] = _data[i] + o._data[i];
		}
		return r;
	}

	Matrix operator -(const Matrix& o) const
	{
		Matrix r(_m, _n);
		for (int i = 0; i < _count; ++i)
		{
			r._data[i] = _data[i] - o._data[i];
		}
		return r;
	}

	Vector getRow(int row) const
	{
		Vector v(_n);
		for (int col = 0; col < _n; ++col)
		{
			int index = row*_n + col;
			v._data[col] = _data[index];
		}
		return v;
	}
	Vector getCol(int col)const 
	{
		Vector v(_m);
		for (int row = 0; row < _m; ++row)
		{
			int index = row*_n + col;
			v._data[row] = _data[index];
		}
		return v;
	}

	// æÿ’Û≥À∑®£∫
	// ◊Û±ﬂµƒ¡–£¨µ»”⁄”“±ﬂµƒ––£¨Ω·π˚ «◊Û±ﬂµƒ––∫Õ”“±ﬂ¡–
	Matrix operator *(const Matrix& o) const
	{
		// *this * o
		// thisµƒ¡–∫Õoµƒ–– «œ‡µ»µƒ
		// this->_n == o._m

		// ∂®“ÂΩ·π˚µƒæÿ’Û£®µ»ª·∂˘“™∑µªÿµƒæÿ’Û£©
		// Ω·π˚æÿ’Ûµƒ––£¨”¶∏√µ»”⁄◊Û±ﬂæÿ’Ûµƒ––
		// Ω·π˚æÿ’Ûµƒ¡–£¨µ»”⁄”“±ﬂæÿ’Ûµƒ¡–
		Matrix r(_m, o._n);

		// ±È¿˙◊Û±ﬂæÿ’Ûµƒ–– ˝
		for (int row = 0; row < _m; ++row)
		{
			// √ø––∂‘”¶µƒœÚ¡ø»°≥ˆ
			Vector v1 = this->getRow(row);

			// ∂‘”¶◊Û±ﬂµƒ√ø“ª––œÚ¡ø£¨“™∫Õƒø±ÍÀ˘”–µƒ¡–£¨Ω¯––µ„≥À
			for (int col = 0; col < o._n; col++)
			{
				Vector v2 = o.getCol(col);

				// µ„≥ÀµƒΩ·π˚£¨∑≈»ÎΩ·π˚æÿ’Ûµƒ
				float result = v1.dot(v2);

				// result∑≈»Îr÷–£¨µ⁄row£¨col¡–
				int index = row* r._n + col;
				r._data[index] = result;

			}
		}
		
		return r;
	}

	int _m, _n;
	int _count;
	float* _data; // ”¶∏√”–m°¡n∏ˆdata

	Matrix& operator=(const Matrix& r) 
	{
		this->_m = r._m;
		this->_n = r._n;
		this->_count = r._count;
		this->_data = new float[_m*_n];
		for (int i = 0; i < _count; ++i)
		{
			_data[i] = r._data[i];
		}
		return *this;
	}
	
	Matrix(const Matrix& r)
	{
		this->_m = r._m;
		this->_n = r._n;
		this->_count = r._count;
		this->_data = new float[_m*_n];
		for (int i = 0; i < _count; ++i)
		{
			_data[i] = r._data[i];
		}
	}

	void dump(const char* name)
	{
		printf("begin %s -------------------------------------------- \n", name);
		for (int row = 0; row < _m; ++row)
		{
			for (int col = 0; col < _n; ++col)
			{
				int index = row*_n + col;
				printf("%f\t", _data[index]);
			}

			printf("\n");
		}
		printf("end %s --------------------------------------------\n", name);
	}
};

