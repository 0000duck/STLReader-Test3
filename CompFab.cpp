//
//  CompFab.cpp
//  voxelizer
//
//
#include "stdafx.h"
#include "CompFab.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <vector>
using namespace CompFab;

CompFab::Vec3 CompFab::operator-(const Vec3 &v1, const Vec3 &v2)
{
	Vec3 v3;
	v3[0] = v1[0] - v2[0];
	v3[1] = v1[1] - v2[1];
	v3[2] = v1[2] - v2[2];
	return v3;
}

CompFab::Vec3 CompFab::operator+(const Vec3 &v1, const Vec3 &v2)
{
	Vec3 v3;
	v3[0] = v1[0] + v2[0];
	v3[1] = v1[1] + v2[1];
	v3[2] = v1[2] + v2[2];

	return v3;
}


//Cross Product
Vec3 CompFab::operator%(const Vec3 &v1, const Vec3 &v2)
{
	Vec3 v3;
	v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
	v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
	v3[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return v3;
}

//Dot Product
float CompFab::operator*(const Vec3 &v1, const Vec3 &v2)
{
	return v1.m_x*v2.m_x + v1.m_y*v2.m_y + v1.m_z*v2.m_z;
}


