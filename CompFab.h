#pragma once
//
//  CompFab.h
//  voxelizer
//
//

#ifndef voxelizer_CompFab_h
#define voxelizer_CompFab_h

#define EPSILON 1e-9

#include <cmath>

namespace CompFab
{
	//Data Types 3D vector and normalize
	typedef struct Vec3Struct
	{
		union
		{
			float m_pos[3];
			struct { float m_x, m_y, m_z; };
		};
		Vec3Struct() :m_x(0.0), m_y(0.0), m_z(0.0) {}
		Vec3Struct(float x, float y, float z) :m_x(x), m_y(y), m_z(z) {}
		inline float & operator[](unsigned int index) { return m_pos[index]; }
		inline const float & operator[](unsigned int index) const { return m_pos[index]; }
		inline void operator+=(const Vec3Struct &a)
		{
			m_x += a.m_x;
			m_y += a.m_y;
			m_z += a.m_z;
		}

	}Vec3;

	// data type triangle (normal and 3 vertices)
	typedef struct TriangleStruct
	{
		Vec3 normal;
		Vec3 m_v1, m_v2, m_v3;
		TriangleStruct(Vec3 normalp, Vec3 v1, Vec3 v2, Vec3 v3) :normal(normalp), m_v1(v1), m_v2(v2), m_v3(v3) {};
	}Triangle;

	//Some useful operations
	//Compute v1 - v2
	Vec3 operator-(const Vec3 &v1, const Vec3 &v2);

	Vec3 operator+(const Vec3 &v1, const Vec3 &v2);

	//Cross Product
	Vec3 operator%(const Vec3 &v1, const Vec3 &v2);

	//Dot Product
	float operator*(const Vec3 &v1, const Vec3 &v2);
}

#endif


