

//
//  Maxtix.cpp
//  OpenGLSnack
//
//  Created by ZhaoPeiWei on 16/1/10.
//  Copyright © 2016年 ZhaoPeiWei. All rights reserved.

#include "Matrix.h"
Matrix::Matrix(int m, int n) :_m(m), _n(n)
{
	_data = new float[m*n];
	_count = m*n;
}


Matrix::~Matrix()
{
	delete[]_data;
}
