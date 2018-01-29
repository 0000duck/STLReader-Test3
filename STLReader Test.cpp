// STLReader Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CompFab.h"
#include "Mesh.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

typedef std::vector<CompFab::Triangle> TriangleList;
TriangleList g_triangleList;

void loadMesh(const std::string& filename, unsigned int dim)
{
	g_triangleList.clear();

	Mesh *tempMesh = new Mesh(filename, true);
	CompFab::Vec3 normalp,v1, v2, v3;

	//copy triangles to global list
	for (unsigned int tri = 0; tri<tempMesh->triangles.size(); ++tri)
	{
		normalp=tempMesh->triangles[tri].normal;
		v1 = tempMesh->triangles[tri].m_v1;
		v2 = tempMesh->triangles[tri].m_v2;
		v3 = tempMesh->triangles[tri].m_v3;
		g_triangleList.push_back(CompFab::Triangle(normalp,v1, v2, v3));
	}
	//Create Voxel Grid
	CompFab::Vec3 bbMax, bbMin;
	BBox(*tempMesh, bbMin, bbMax);

	//Build Voxel Grid
	float bbX = bbMax[0] - bbMin[0];
	float bbY = bbMax[1] - bbMin[1];
	float bbZ = bbMax[2] - bbMin[2];
	float spacing;

	if (bbX > bbY && bbX > bbZ)
	{
		spacing = bbX / (float)(dim - 2);
	}
	else if (bbY > bbX && bbY > bbZ) {
		spacing = bbY / (float)(dim - 2);
	}
	else {
		spacing = bbZ / (float)(dim - 2);
	}

	CompFab::Vec3 hspacing(0.5*spacing, 0.5*spacing, 0.5*spacing);

	delete tempMesh;
}

void exportMesh(const std::string& filename) {
	Mesh mout;
	mout.triangles = g_triangleList;
	mout.export_stl(filename);
};

int main()
{
	std::string input_filename = "./Scan1_flatneighbors2.stl";
	unsigned int size = 32;
	loadMesh(input_filename, size);

	for (unsigned int ii = 0; ii < g_triangleList.size(); ++ii) {
		std::cout << g_triangleList[ii].m_v1.m_x <<"  "<< g_triangleList[ii].m_v1.m_y<<"  "<<g_triangleList[ii].m_v1.m_z<< std::endl;
		std::cout << g_triangleList[ii].m_v2.m_x <<" "<< g_triangleList[ii].m_v2.m_y << "  " << g_triangleList[ii].m_v2.m_z << std::endl;
		std::cout << g_triangleList[ii].m_v3.m_x << "  " << g_triangleList[ii].m_v3.m_y << "  " << g_triangleList[ii].m_v3.m_z << std::endl;

	}
    return 0;
}

